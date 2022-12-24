#pragma once

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "quadrature.h"

#include "ssd1315.h"

#define LED_PIN 25

class PicoProgram {
    public:
        PicoProgram();
        void Setup();
        void Loop();

        Quadrature quad_enc;

        bool led = true;
        bool oled = false;
        uint8_t timing = 0;
        bool update = false;
        repeating_timer_t r_timer;

        static void handle_gpio(uint gpio, uint32_t event_mask);
        static bool timer_callback(repeating_timer_t *rt);
    
    private:
        void display_string(unsigned char * buf, int pos_x, int pos_y, int len);
        void do_cursor(unsigned char *buf);
        uint8_t pattern = 0b00110011;
        uint8_t oled_buf[OLED_BUF_LEN];

        char s_line1[17] = "**Coil-Winder**?";
        char s_line2[17] = "1234567890ABCDEF";
        char s_line3[17] = "ABCDEFGHIJKLMNOP";
        char s_line4[17]; // = "QRSTUVWXYZ<>-=+!";

        bool sel_b = false;
        uint8_t sel_w = 1;
        uint8_t sel_x = 2;
        uint8_t sel_y = 0;
};

extern PicoProgram program;
