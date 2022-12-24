#pragma once

#include "ssd1315.h"

class Display {
    public:
        Display();
        void Setup();
        void display_string(unsigned char * buf, int pos_x, int pos_y, int len);
        void do_cursor();
        void SendBuffer();
        inline void SetCursor(uint8_t x, uint8_t y, uint8_t z) { sel_x = x; sel_y = y; sel_z = z;}
        inline void SetCursorB(bool b) { sel_b = b;}
        inline uint8_t GetCursorX() { return sel_x; }
        inline uint8_t GetCursorY() { return sel_y; }
        inline uint8_t GetCursorZ() { return sel_z; }
    private:
        uint8_t oled_buf[OLED_BUF_LEN];
        bool sel_b = false;
        uint8_t sel_x = 2;
        uint8_t sel_y = 0;
        uint8_t sel_z = 1;
};