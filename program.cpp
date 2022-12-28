#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "pico/binary_info.h"

#include "program.h"

#include "buttons.h"
#include "quadrature.h"
#include "display.h"

p_params::p_params(
        uint16_t x_offset,
        uint16_t windings_per_layer,
        uint16_t layer_width,
        uint16_t coil_windings,
        uint16_t steps_per_rev,
        uint16_t steps_per_mm
    ) {
    this->x_offset = x_offset;
    this->windings_per_layer = windings_per_layer;
    this->layer_width = layer_width;
    this->coil_windings = coil_windings;
    this->steps_per_rev = steps_per_rev;
    this->steps_per_mm = steps_per_mm;
}

PicoProgram::PicoProgram() : params(20, 14, 10, 250, 200 * 16, 25 * 16) {
    // Constructor
}

void PicoProgram::handle_gpio(uint gpio, uint32_t event_mask) {
    if(gpio == UI_B1) {
        if(event_mask & GPIO_IRQ_EDGE_RISE && program.menu_offset > 0) program.menu_offset--;
    }
    if(gpio == UI_B2) {
        if(event_mask & GPIO_IRQ_EDGE_RISE) program.menu_offset++;
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

        //sprintf(s_line[3], "d%02x o%02x n%02x P%02x", quad_enc.delta, quad_enc.enc_old, quad_enc.enc_new, quad_enc.enc_pos);
        //if(menu_offset < 0) menu_offset = 0;
        //if(menu_offset > (MENU_ITEMS - 3)) menu_offset = (MENU_ITEMS - 3);
        for(uint8_t a = 1; a < 4; a++) {
            //for(uint8_t b = 0; b<16; b++) s_line[a][b] = ' ';
            uint8_t item = (a-1) + ((uint8_t)menu_offset);
            if(item >= MENU_ITEMS)
                sprintf(s_line[a],"----------------");
            else {
                sprintf(s_line[a],"%-8s%8d",menus[item].label, menus[item].value);
                //sprintf(&(s_line[a][menus[item].pt.x]),"%d", menus[item].value);
            }
        }

        for(uint8_t a=0; a<4; a++) {
            disp.display_string((unsigned char *)s_line[a],0,a,16);
        }

        if(oled)
            disp.AllOn();
        else
            disp.ShowRAM();

        disp.do_cursor((bool)((timing & 0x08) >> 3));
        disp.SendBuffer();
    }
}