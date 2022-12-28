#include <stdio.h>

#include "display.h"

#include "ssd1315.h"
#include "font.h"

Display::Display() : c(2,0,1) {
    // Constructor
}

void Display::Setup() {
    ssd1315_setup_i2c();
    ssd1315_init();
    //ssd1315_address_mode(SSD1315_ADDRMODE_HORIZONTAL);
    ssd1315_address_mode(SSD1315_ADDRMODE_VERTICAL);
    //ssd1315_set_page_addr(0x00, 0x03);
    //ssd1315_set_column_addr(0x00, 0x7F);

    //ssd1315_send_cmd(SSD1315_CMD_DISPLAY_ENTIRE_ON);

    for(int a=0; a < OLED_BUF_LEN; a++) oled_buf[a] = 0;
    ssd1315_send_data(oled_buf, OLED_BUF_LEN);
}

void Display::AllOn() {
    ssd1315_send_cmd(SSD1315_CMD_DISPLAY_ENTIRE_ON);
}

void Display::ShowRAM() {
    ssd1315_send_cmd(SSD1315_CMD_DISPLAY_RAM);
}

void Display::SendBuffer() {
    ssd1315_send_data(oled_buf, OLED_BUF_LEN);
}

void Display::display_string(unsigned char * buf, int pos_x, int pos_y, int len) {
    for(int a = 0; a < len; a++) {
        if(buf[a] == 0) break;
        font_to_buffer(font8x16, oled_buf,pos_x + (a << 3),pos_y, OLED_NUM_PAGES, buf[a]);
    }
}

void Display::do_cursor(bool blink) {
    uint baddr;
    if(blink && c.visible) {
        baddr = ((c.x<<3) * OLED_NUM_PAGES) + ((c.y & 0x03)<<1) ;
        for(int a = 0; a < c.z << 3; a++) {
            oled_buf[baddr] = ~oled_buf[baddr];
            oled_buf[baddr+1] = ~oled_buf[baddr+1];
            baddr += OLED_NUM_PAGES;
        }
    }
}
