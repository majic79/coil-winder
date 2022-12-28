#pragma once

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "quadrature.h"
#include "buttons.h"
#include "display.h"

#include "menu.h"

#define LED_PIN 25

#define MENU_ITEMS 6

struct p_params {
    p_params(
        uint16_t x_offset,
        uint16_t windings_per_layer,
        uint16_t layer_width,
        uint16_t coil_windings,
        uint16_t steps_per_rev,
        uint16_t steps_per_mm
    );
    uint16_t x_offset;
    uint16_t windings_per_layer;
    uint16_t layer_width;
    uint16_t coil_windings;
    uint16_t steps_per_rev; // Steps per revolution
    uint16_t steps_per_mm; // Steps per mm of Z travel
};

typedef struct p_params ProgramParameters;

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
        uint8_t menu_offset = 0;
        char s_line[4][17] = {"**Coil--Winder**","1234567890ABCDEF","ABCDEFGHIJKLMNOP","----------------"};

        ProgramParameters params;

        MenuItem menus[MENU_ITEMS] = {
            MenuItem(8,0,0,params.x_offset,"offset"),
            MenuItem(8,0,0,params.windings_per_layer,"w/layer"),
            MenuItem(8,0,0,params.layer_width,"l/width"),
            MenuItem(8,0,0,params.coil_windings,"winds"),
            MenuItem(8,0,0,params.steps_per_rev,"s/rev"),
            MenuItem(8,0,0,params.steps_per_mm,"s/mm")
        };
};

extern PicoProgram program;
