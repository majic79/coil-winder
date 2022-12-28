#pragma once

#include "cursor.h"

class MenuItem {
    public:
        MenuItem(uint8_t x,uint8_t y,uint8_t z, int16_t value, const char* label);
        Cursor_Point pt;
        int16_t value;
        const char* label;
};