#include "quadrature.h"

#include "hardware/clocks.h"
#include "hardware/gpio.h"

#include "quadrature_encoder.pio.h"

Quadrature::Quadrature() {
    // Constructor
}

void Quadrature::Setup() {
    gpio_init(UI_RE_A);
    gpio_init(UI_RE_B);

    uint offset = pio_add_program(pio, &quadrature_encoder_program);
 
    //quadrature_encoder_program_init(pio, pio_sm, offset, UI_RE_A, 65535);
	pio_sm_set_consecutive_pindirs(pio, pio_sm, UI_RE_A, 2, false);
	gpio_pull_up(UI_RE_A);
	gpio_pull_up(UI_RE_A + 1);

	pio_sm_config c = quadrature_encoder_program_get_default_config(offset);
	sm_config_set_in_pins(&c, UI_RE_A); // for WAIT, IN
	sm_config_set_jmp_pin(&c, UI_RE_A); // for JMP
	// shift to left, autopull disabled
	sm_config_set_in_shift(&c, false, false, 32);
	// don't join FIFO's
	sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_NONE);

    // one state machine loop takes at most 14 cycles
    float div = (float)clock_get_hz(clk_sys) / (14 * 65535);
    sm_config_set_clkdiv(&c, div);

	pio_sm_init(pio, pio_sm, offset, &c);
	pio_sm_set_enabled(pio, pio_sm, true);

}

void Quadrature::Update() {
    enc_new = (uint8_t)(get_count(pio, pio_sm) & 0xFF);
    delta = enc_new - enc_old;
    enc_old = enc_new;

    enc_pos -= delta;
}
