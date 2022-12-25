#pragma once

#include "ssd1315.h"
#include "cursor.h"

class Display {
    public:
        Display();
        void Setup();
        void display_string(unsigned char * buf, int pos_x, int pos_y, int len);
        void do_cursor();
        void SendBuffer();
        void ShowRAM();
        void AllOn();
        inline void SetCursorB(bool b) { sel_b = b;}
        Cursor c;

    private:
        uint8_t oled_buf[OLED_BUF_LEN];
        bool sel_b = false;
};