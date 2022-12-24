#include "hardware/gpio.h"
#include "buttons.h"

Buttons::Buttons() {
    // Constructor
}

void Buttons::Setup() {
    gpio_init(UI_B1);
    gpio_init(UI_B2);
    gpio_init(UI_RE_SW);

    gpio_set_dir(UI_B1, GPIO_IN);
    gpio_set_dir(UI_B2, GPIO_IN);
    gpio_set_dir(UI_RE_SW, GPIO_IN);

    gpio_pull_down(UI_B1);
    gpio_pull_down(UI_B2);
    gpio_pull_up(UI_RE_SW);

    gpio_set_irq_enabled(UI_B1, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(UI_B2, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(UI_RE_SW, GPIO_IRQ_EDGE_FALL, true);
}
