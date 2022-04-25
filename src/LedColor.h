//
// Created by morgan on 4/24/2022.
//

#ifndef PLATFORMIO_PROGRAM_LEDCOLOR_H
#define PLATFORMIO_PROGRAM_LEDCOLOR_H

#include "ILedColor.h"

class LedColor : public ILedColor {
public:
    LedColor(uint8_t r, uint8_t g, uint8_t b) : ILedColor(r,g,b)
//    : ILedColor(r, g, b)
    {

    }

};

#endif //PLATFORMIO_PROGRAM_LEDCOLOR_H