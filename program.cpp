#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "pico/binary_info.h"

#include "program.h"

#include "buttons.h"
#include "quadrature.h"
#include "display.h"

PicoProgram::PicoProgram() {
    // Constructor
}

void PicoProgram::handle_gpio(uint gpio, uint32_t event_mask) {
    if(gpio == UI_B1) {
        if(event_mask & GPIO_IRQ_EDGE_RISE) program.quad_enc.Dec();
    }
    if(gpio == UI_B2) {
        if(event_mask & GPIO_IRQ_EDGE_RISE) program.quad_enc.Inc();
    }
    /*
    if(gpio == UI_RE_A) {
        if(event_mask & GPIO_IRQ_EDGE_RISE) led = true;
    }github
    if(gpio == UI_RE_B) {
        if(event_mask & GPIO_IRQ_EDGE_RISE) led = false;
    }
    */
    if(gpio == UI_RE_SW) {
        if(event_mask & GPIO_IRQ_EDGE_FALL) program.oled = !program.oled;
    }
}

bool PicoProgram::timer_callback(repeating_timer_t *rt) {
    //led = !led;
    program.timing++;
    program.update = true;
    return true;
}


void PicoProgram::Setup() {
    // Program setup phase
    stdio_init_all();

    // Turn the light on to let the world know we're alive
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, true);

    buttons.Setup();
    quad_enc.Setup();

    gpio_set_irq_callback(PicoProgram::handle_gpio);
    irq_set_enabled(IO_IRQ_BANK0, true);

    add_repeating_timer_us(-100000, PicoProgram::timer_callback, NULL, &this->r_timer);

    disp.Setup();
}

void PicoProgram::Loop() {
    // Program loop
    if(update) {
        uint8_t new_x;
        update = false;
        quad_enc.Update();
        uint8_t enc_pos = quad_enc.Pos();

        new_x = (enc_pos>>1) & 0x0F;
        if(new_x != disp.c.x) {
            timing = 0x08;
            disp.c.x = new_x;
        }

        // Do we display cursor?
        disp.SetCursorB((bool)((timing & 0x08) >> 3));

        sprintf(s_line4, "d%02x o%02x n%02x P%02x", quad_enc.delta, quad_enc.enc_old, quad_enc.enc_new, quad_enc.enc_pos);
        disp.display_string((unsigned char *)s_line1,0,0,16);
        disp.display_string((unsigned char *)s_line2,0,1,16);
        disp.display_string((unsigned char *)s_line3,0,2,16);
        disp.display_string((unsigned char *)s_line4,0,3,16);

        if(oled)
            disp.AllOn();
        else
            disp.ShowRAM();
        //sel_b = !sel_b;
        disp.do_cursor();
        disp.SendBuffer();
    }
}