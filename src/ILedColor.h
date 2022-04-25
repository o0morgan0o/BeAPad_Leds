//
// Created by morgan on 4/24/2022.
//

#ifndef PLATFORMIO_PROGRAM_ILEDCOLOR_H
#define PLATFORMIO_PROGRAM_ILEDCOLOR_H

#include <Arduino.h>

class ILedColor {
public:
    ILedColor(uint8_t r, uint8_t g, uint8_t b) {
        _r = r;
        _g = g;
        _b = b;
    }

private:
    uint8_t _r;
    uint8_t _g;
    uint8_t _b;
};

#endif //PLATFORMIO_PROGRAM_ILEDCOLOR_H