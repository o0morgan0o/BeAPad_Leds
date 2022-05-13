//
// Created by morgan on 5/8/2022.
//

#ifndef PLATFORMIO_PROGRAM_LEDBOARD_STORE_NEOPIXELSTORE_H
#define PLATFORMIO_PROGRAM_LEDBOARD_STORE_NEOPIXELSTORE_H

#include "LedBoard_Store_Interface.h"
#include <Adafruit_NeoPixel.h>

class LedBoard_Store_NeoPixelStore : public LedBoard_Store_Interface {
public:
    LedBoard_Store_NeoPixelStore() : LedBoard_Store_Interface() {
    }

};

#endif //PLATFORMIO_PROGRAM_LEDBOARD_STORE_NEOPIXELSTORE_H