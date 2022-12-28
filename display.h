#pragma once

#include "ssd1315.h"
#include "cursor.h"

class Display {
    public:
        Display();
        void Setup();
        void display_string(unsigned char * buf, int pos_x, int pos_y, int len);
        void do_cursor(bool blink);
        void SendBuffer();
        void ShowRAM();
        void AllOn();
        Cursor c;

    private:
        uint8_t oled_buf[OLED_BUF_LEN];
};