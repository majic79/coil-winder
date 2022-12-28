#include "menu.h"

MenuItem::MenuItem(uint8_t x,uint8_t y,uint8_t z, int16_t value, const char* label) {
    // Constructor
    this->pt.x = x;
    this->pt.y = y;
    this->pt.z = z;
    this->value = value;
    this->label = label;
}
