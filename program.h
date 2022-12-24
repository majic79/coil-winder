#pragma once

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "quadrature.h"
#include "buttons.h"
#include "display.h"

#define LED_PIN 25

class PicoProgram {
    public:
        PicoProgram();
        void Setup();
        void Loop();
        Buttons buttons;
        Quadrature quad_enc;
        Display disp;
        bool led = true;
        bool oled = false;
        uint8_t timing = 0;
        bool update = false;
        repeating_timer_t r_timer;

        static void handle_gpio(uint gpio, uint32_t event_mask);
        static bool timer_callback(repeating_timer_t *rt);
    
    private:
        uint8_t pattern = 0b00110011;

        char s_line1[17] = "**Coil--Winder**";
        char s_line2[17] = "1234567890ABCDEF";
        char s_line3[17] = "ABCDEFGHIJKLMNOP";
        char s_line4[17]; // = "QRSTUVWXYZ<>-=+!";
};

extern PicoProgram program;
