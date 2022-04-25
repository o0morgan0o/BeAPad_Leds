//
// Created by morgan on 4/24/2022.
//

#ifndef PLATFORMIO_PROGRAM_LEDBOARD_STORE_FASTLEDSTORE_H
#define PLATFORMIO_PROGRAM_LEDBOARD_STORE_FASTLEDSTORE_H

#include "LedBoard_Store_Interface.h"
#include "LedStrip_Holder_Interface.h"
#include <FastLED.h>
#include "FastLedLedBoard.h"

class LedBoard_Store_FastLedStore : public LedBoard_Store_Interface {
public:
    LedBoard_Store_FastLedStore() : LedBoard_Store_Interface() {
//        // Creation of FastLed multiple arrays
        FastLED.addLeds<NEOPIXEL, 13>(ledStrip0, 9);
        FastLED.addLeds<NEOPIXEL, 12>(ledStrip1, 9);
        FastLED.addLeds<NEOPIXEL, 14>(ledStrip2, 9);
        FastLED.addLeds<NEOPIXEL, 27>(ledStrip3, 9);
        FastLED.addLeds<NEOPIXEL, 26>(ledStrip4, 9);
        FastLED.addLeds<NEOPIXEL, 25>(ledStrip5, 9);
        FastLED.addLeds<NEOPIXEL, 33>(ledStrip6, 9);
        FastLED.addLeds<NEOPIXEL, 32>(ledStrip7, 9);
//
    }
//
//    void giveReferenceManager(LedBoardsManager *manager) override {
//        auto ledBoards = manager->getLedBoards();
//        _ledBoards.at(0)->giveReferenceManager(ledStrip1, 13, manager);
//
//    }





public:
};

#endif //PLATFORMIO_PROGRAM_LEDBOARD_STORE_FASTLEDSTORE_H