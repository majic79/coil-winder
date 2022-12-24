#pragma once

#ifdef __cplusplus
extern "C" {
#endif

extern const unsigned char digital_font5x7_123[];
extern const unsigned char font8x16[];

void font_to_buffer(const unsigned char *font, unsigned char *buf, int pos_x, int pos_y, int display_height, char c);
//void font_to_buffer(uint8_t *font, uint8_t *buf, int pos_x, int pos_y, int display_height, char c);
//int font_to_buffer(uint8_t *font, uint8_t *buf, int height, int width, char *sz);

#ifdef __cplusplus
}
#endif