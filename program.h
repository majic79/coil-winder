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

        char s_line[4][17] = {"**Coil--Winder**","1234567890ABCDEF","ABCDEFGHIJKLMNOP","----------------"};
};

extern PicoProgram program;
