#pragma once

#include <stdio.h>

struct cursor_point{
    uint8_t x;
    uint8_t y;
    uint8_t z;
};
typedef struct cursor_point Cursor_Point;

class Cursor : public Cursor_Point {
    public:
        Cursor(uint8_t x, uint8_t y, uint8_t z);
        bool visible = false;
        bool blink = false;
    private:
};