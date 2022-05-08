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
//        _strips.emplace_back(new Adafruit_NeoPixel{NUM_PIXELS_PER_BOARD, 25, NEO_GRB + NEO_KHZ800});

//        // TODO move initialization in another class
//        for (auto strip: _strips) {
//            strip->begin();
//        }

    }

    void initAllBoards() override {
        for(auto board: _ledBoards){
            board->initBoard();
        }
    }

private:
    uint8_t NUM_PIXELS_PER_BOARD = 9;



};

#endif //PLATFORMIO_PROGRAM_LEDBOARD_STORE_NEOPIXELSTORE_H