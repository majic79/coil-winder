#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
//#include "hardware/i2c.h"
#include "pico/binary_info.h"

#include "ssd1315.h"
#include "font.h"
#include "buttons.h"

#include "quadrature_encoder.pio.h"

#define LED_PIN 25

bool update = false;
bool led = true;


repeating_timer_t r_timer;

// Use PIO 0
PIO pio = pio0;
// Use State Machine 0;
const uint pio_sm = 0;
uint8_t enc_old=0, delta, enc_new;

bool lp = 0;
uint8_t s = 0;

bool oled = false;

uint8_t pattern = 0b00110011;

uint8_t timing = 0;

uint8_t oled_buf[OLED_BUF_LEN];

char s_line1[17] = "**Coil-Winder**?";
char s_line2[17] = "1234567890ABCDEF";
char s_line3[17] = "ABCDEFGHIJKLMNOP";
char s_line4[17]; // = "QRSTUVWXYZ<>-=+!";

bool sel_b = false;
uint8_t sel_w = 1;
uint8_t sel_x = 2;
uint8_t sel_y = 0;

void handle_gpio(uint gpio, uint32_t event_mask) {
    //uint32_t tick = time_us_32();
    if(gpio == UI_B1) {
        if(event_mask & GPIO_IRQ_EDGE_RISE) enc_pos--;
    }
    if(gpio == UI_B2) {
        if(event_mask & GPIO_IRQ_EDGE_RISE) enc_pos++;
    }
    /*
    if(gpio == UI_RE_A) {
        if(event_mask & GPIO_IRQ_EDGE_RISE) led = true;
    }
    if(gpio == UI_RE_B) {
        if(event_mask & GPIO_IRQ_EDGE_RISE) led = false;
    }
    */
    if(gpio == UI_RE_SW) {
        if(event_mask & GPIO_IRQ_EDGE_FALL) oled = !oled;
    }
}

bool timer_callback(repeating_timer_t *rt) {
    //led = !led;
    timing++;
    update = true;
    return true;
}

void display_string(unsigned char * buf, int pos_x, int pos_y, int len) {
    for(int a = 0; a < len; a++) {
        if(buf[a] == 0) break;
        font_to_buffer(font8x16, oled_buf,pos_x + (a << 3),pos_y, OLED_NUM_PAGES, buf[a]);
    }
}

void do_cursor(unsigned char *buf) {
    uint baddr;
    if(sel_b) {
        baddr = ((sel_x<<3) * OLED_NUM_PAGES) + (sel_y) ;
        for(int a = 0; a < sel_w << 3; a++) {
            buf[baddr] = ~buf[baddr];
            buf[baddr+1] = ~buf[baddr+1];
            baddr += OLED_NUM_PAGES;
        }
    }

}

void setup() {
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    setup_buttons();

    gpio_set_irq_enabled(UI_B1, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(UI_B2, GPIO_IRQ_EDGE_RISE, true);
    //gpio_set_irq_enabled(UI_RE_A, GPIO_IRQ_EDGE_RISE, true);
    //gpio_set_irq_enabled(UI_RE_B, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(UI_RE_SW, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_callback(handle_gpio);
    irq_set_enabled(IO_IRQ_BANK0, true);

    uint offset = pio_add_program(pio, &quadrature_encoder_program);
    quadrature_encoder_program_init(pio, pio_sm, offset, UI_RE_A, 65535);

    ssd1315_setup_i2c();
    ssd1315_init();
    //ssd1315_address_mode(SSD1315_ADDRMODE_HORIZONTAL);
    ssd1315_address_mode(SSD1315_ADDRMODE_VERTICAL);
    //ssd1315_set_page_addr(0x00, 0x03);
    //ssd1315_set_column_addr(0x00, 0x7F);

    add_repeating_timer_us(-100000, timer_callback, NULL, &r_timer);

    //ssd1315_send_cmd(SSD1315_CMD_DISPLAY_ENTIRE_ON);

    for(int a=0; a < OLED_BUF_LEN; a++) oled_buf[a] = 0;
    ssd1315_send_data(oled_buf, OLED_BUF_LEN);

}

void loop() {
    //read_encoder();
    if(update) {
        uint8_t new_x;
        update = false;

        enc_new = (uint8_t)(quadrature_encoder_get_count(pio, pio_sm) & 0xFF);
        delta = enc_new - enc_old;
        enc_old = enc_new;

        enc_pos -= delta;
        new_x = (enc_pos>>1) & 0x0F;
        if(new_x != sel_x) {
            timing = 0x08;
            sel_x = new_x;
        }

        // Do we display cursor?
        sel_b = (bool)((timing & 0x08) >> 3);

        sprintf(s_line4, "d%02x o%02x n%02x P%02x", delta, enc_old, enc_new, enc_pos);
        display_string(s_line1,0,0,16);
        display_string(s_line2,0,1,16);
        display_string(s_line3,0,2,16);
        display_string(s_line4,0,3,16);

        if(oled)
            ssd1315_send_cmd(SSD1315_CMD_DISPLAY_ENTIRE_ON);
        else
            ssd1315_send_cmd(SSD1315_CMD_DISPLAY_RAM);
        //sel_b = !sel_b;
        do_cursor(oled_buf);
        ssd1315_send_data(oled_buf, OLED_BUF_LEN);
    }
}

int main() {
    bi_decl(bi_program_description("Coil-Winder Rev Counter"));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));
    bi_decl(bi_1pin_with_name(UI_B1, "User Interface - Button 1"));
    bi_decl(bi_1pin_with_name(UI_B2, "User Interface - Button 2"));
    bi_decl(bi_1pin_with_name(UI_RE_A, "User Interface - Rotary Encoder A"));
    bi_decl(bi_1pin_with_name(UI_RE_B, "User Interface - Rotary Encoder B"));
    bi_decl(bi_1pin_with_name(UI_RE_SW, "User Interface - Rotary Encoder SW"));
    bi_decl(bi_2pins_with_func(PICO_SSD1315_I2C_SDA_PIN, PICO_SSD1315_I2C_SCL_PIN, GPIO_FUNC_I2C));
    setup();

    gpio_put(LED_PIN, led);

    while(1) {
        loop();
    } 
    return 0;
}