#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
//#include "hardware/i2c.h"
#include "pico/binary_info.h"

#include "ssd1315.h"
#include "font.h"
#include "buttons.h"

#include "program.h"

#include "quadrature_encoder.pio.h"

PicoProgram program;

int main() {
    bi_decl(bi_program_description("Coil-Winder Rev Counter"));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));
    bi_decl(bi_1pin_with_name(UI_B1, "User Interface - Button 1"));
    bi_decl(bi_1pin_with_name(UI_B2, "User Interface - Button 2"));
    bi_decl(bi_1pin_with_name(UI_RE_A, "User Interface - Rotary Encoder A"));
    bi_decl(bi_1pin_with_name(UI_RE_B, "User Interface - Rotary Encoder B"));
    bi_decl(bi_1pin_with_name(UI_RE_SW, "User Interface - Rotary Encoder SW"));
    bi_decl(bi_2pins_with_func(PICO_SSD1315_I2C_SDA_PIN, PICO_SSD1315_I2C_SCL_PIN, GPIO_FUNC_I2C));
    program.Setup();

    while(1) {
        program.Loop();
    } 
    return 0;
}