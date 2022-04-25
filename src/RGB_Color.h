//
// Created by morgan on 4/25/2022.
//

#ifndef PLATFORMIO_PROGRAM_RGB_COLOR_H
#define PLATFORMIO_PROGRAM_RGB_COLOR_H

#include "Arduino.h"

struct RGB_Color {
    RGB_Color(uint8_t r, uint8_t g, uint8_t b) {
        _r = r;
        _g = g;
        _b = b;
    }

    uint8_t _r;
    uint8_t _g;
    uint8_t _b;

};

#endif //PLATFORMIO_PROGRAM_RGB_COLOR_H