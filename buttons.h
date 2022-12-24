#pragma once

#define UI_B1 12
#define UI_B2 13

#define UI_RE_A 14
#define UI_RE_B 15
#define UI_RE_SW 22

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t enc_pos;

void setup_buttons();

#ifdef __cplusplus
}
#endif