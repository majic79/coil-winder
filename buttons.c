#include "hardware/gpio.h"
#include "buttons.h"

void setup_buttons() {
    gpio_init(UI_B1);
    gpio_init(UI_B2);
    gpio_init(UI_RE_SW);

    gpio_set_dir(UI_B1, GPIO_IN);
    gpio_set_dir(UI_B2, GPIO_IN);
//    gpio_set_dir(UI_RE_A, GPIO_IN);
//    gpio_set_dir(UI_RE_B, GPIO_IN);
    gpio_set_dir(UI_RE_SW, GPIO_IN);

//    gpio_pull_up(UI_RE_A);
//    gpio_pull_up(UI_RE_B);
    gpio_pull_up(UI_RE_SW);

    gpio_pull_down(UI_B1);
    gpio_pull_down(UI_B2);

    gpio_set_irq_enabled(UI_RE_SW, GPIO_IRQ_EDGE_FALL, true);

//    enc_prev = enc_curr = ((uint8_t)gpio_get(UI_RE_A) << 1) | gpio_get(UI_RE_B);
}
