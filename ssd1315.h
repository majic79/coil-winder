#pragma once

// Driver library for SSD1315
// Datasheet: https://cursedhardware.github.io/epd-driver-ic/SSD1315.pdf

#define SSD1315_CTRL_CMD ((uint8_t)0x80)
#define SSD1315_CTRL_DATA ((uint8_t)0x40)

// Charge pump bump setting
#define SSD1315_CMD_CHARGE_PUMP         ((uint8_t)0x8D)
#define SSD1315_CHARGE_PUMP_EN         ((uint8_t)0x14)


// Fundamental Commands
#define SSD1315_CMD_CONTRAST            ((uint8_t)0x81)

#define SSD1315_CMD_DISPLAY_RAM         ((uint8_t)0xA4)
#define SSD1315_CMD_DISPLAY_ENTIRE_ON   ((uint8_t)0xA5)

#define SSD1315_CMD_DISPLAY_NORMAL      ((uint8_t)0xA6)
#define SSD1315_CMD_DISPLAY_INVERSE     ((uint8_t)0xA7)

#define SSD1315_CMD_DISPLAY_OFF         ((uint8_t)0xAE)
#define SSD1315_CMD_DISPLAY_ON          ((uint8_t)0xAF)

// Scroll Commands
#define SSD1315_CMD_HSCROLL             ((uint8_t)0x26)
#define SSD1315_CMD_VSCROLL             ((uint8_t)0x26)
#define SSD1315_CMD_SCROLL_STOP         ((uint8_t)0x2E)
#define SSD1315_CMD_SCROLL_START        ((uint8_t)0x2F)

#define SSD1315_CMD_SET_VSCROLL_AREA    ((uint8_t)0xA3)

// Address Setting Commands
#define SSD1315_CMD_LOWER_COL_START     ((uint8_t)0x00) // Lower nibble column start address in X[3:0]
#define SSD1315_CMD_UPPER_COL_START     ((uint8_t)0x10) // Upper nibble column start address in X[3:0]

#define SSD1315_CMD_MEM_ADDRESS_MODE    ((uint8_t)0x20)
#define SSD1315_ADDRMODE_HORIZONTAL     ((uint8_t)0x00)
#define SSD1315_ADDRMODE_VERTICAL       ((uint8_t)0x01)
#define SSD1315_ADDRMODE_PAGE           ((uint8_t)0x02)

#define SSD1315_CMD_COL_ADDR            ((uint8_t)0x21) // Follow with two byte column start and end
#define SSD1315_CMD_PAGE_ADDR           ((uint8_t)0x22) // Follow with two byte page start and end

#define SSD1315_CMD_PAGE_START          ((uint8_t)0xB0) // OR with three bit page start address for page addressing

// Hardware Configuration
#define SSD1315_CMD_

#define SSD1315_CMD_DISPLAY_START_LINE  ((uint8_t)0x40)
#define SSD1315_CMD_SEGMENT_REMAP       ((uint8_t)0xA0) // LSB = 0|1 (col 0 maps to SEG0|col 127 maps to SEG0)

#define SSD1315_CMD_MUX_RATIO           ((uint8_t)0xA8) // Set height of display in following byte

#define SSD1315_CMD_COM_SCAN_DIR        ((uint8_t)0xC0)
#define SSD1315_COM_SCAN_NORMAL         ((uint8_t)0x00)
#define SSD1315_COM_SCAN_REVERSE        ((uint8_t)0x08)

#define SSD1315_CMD_DISPLAY_OFFSET      ((uint8_t)0xD3) // set vertical shift display offset in following byte

#define SSD1315_CMD_COM_PIN_CFG         ((uint8_t)0xDA) // Follow with hardware pin configuration
#define SSD1315_COM_PIN_SEQ             ((uint8_t)0x02)
#define SSD1315_COM_PIN_ALT             ((uint8_t)0x12)
#define SSD1315_COM_PIN_DISABLE_LR      ((uint8_t)0x02)
#define SSD1315_COM_PIN_ENABLE_LR       ((uint8_t)0x22)

// Timing and Driving - See Datasheet for timing information
#define SSD1315_CMD_OSC_CLK_DIV         ((uint8_t)0xD5) // Follow with clock div/freq
#define SSD1315_CMD_PRECHARGE           ((uint8_t)0xD9) // Follow with precharge period
#define SSD1315_CMD_VCOM_DESEL          ((uint8_t)0xDB) // Follow with Vcomh Deselect level
#define SSD1315_VCOM_065                ((uint8_t)0x00)
#define SSD1315_VCOM_077                ((uint8_t)0x20)
#define SSD1315_VCOM_085                ((uint8_t)0x30)

// Pico I2C Information

#define SSD1315_I2C_ADDR ((uint8_t)0x3C)
#define OLED_HEIGHT 64
#define OLED_WIDTH 128
#define OLED_PAGE_HEIGHT 8
#define OLED_NUM_PAGES OLED_HEIGHT / OLED_PAGE_HEIGHT
#define OLED_BUF_LEN (OLED_NUM_PAGES * OLED_WIDTH)

#define PICO_SSD1315_I2C i2c0
#define PICO_SSD1315_I2C_SDA_PIN 4
#define PICO_SSD1315_I2C_SCL_PIN 5

#ifdef __cplusplus
extern "C" {
#endif

void ssd1315_setup_i2c();
void ssd1315_send_cmd(uint8_t cmd);
void ssd1315_init();
void ssd1315_set_precharge(uint8_t c);
void ssd1315_address_mode(uint8_t ssd1315_address_mode);

void ssd1315_repeat_fill(uint8_t c);

void ssd1315_send_data(uint8_t sbuf[], int buflen);

void ssd1315_set_page_addr(uint8_t start, uint8_t end);
void ssd1315_set_page_start(uint8_t start);

void ssd1315_set_column_addr(uint8_t start, uint8_t end);

#ifdef __cplusplus
}
#endif