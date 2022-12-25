#pragma once

#include <stdio.h>

class Cursor {
    public:
        Cursor(uint8_t x, uint8_t y, uint8_t z);
        uint8_t x;  // X position
        uint8_t y;  // Y position
        uint8_t z;  // Z = Length of cursor
    private:
};