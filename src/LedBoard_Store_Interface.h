//
// Created by morgan on 4/24/2022.
//

#ifndef PLATFORMIO_PROGRAM_LEDBOARD_STORE_INTERFACE_H
#define PLATFORMIO_PROGRAM_LEDBOARD_STORE_INTERFACE_H

#include <vector>
#include "LedBoard.h"
#include "Adafruit_NeoPixel.h"

class LedBoard_Store_Interface {
public:
//    virtual void giveReferenceManager(LedBoardsManager *manager) = 0;

    virtual void addBoard(LedBoard *ledBoard) { _ledBoards.emplace_back(ledBoard); };

    std::vector<LedBoard *> getLedBoards() { return _ledBoards; }

    virtual void initAllBoards(){}

public:
    CRGB ledStrip0[9]{};
    CRGB ledStrip1[9]{};
    CRGB ledStrip2[9]{};
    CRGB ledStrip3[9]{};
    CRGB ledStrip4[9]{};
    CRGB ledStrip5[9]{};
    CRGB ledStrip6[9]{};
    CRGB ledStrip7[9]{};
protected:
    std::vector<LedBoard *> _ledBoards;

};

#endif //PLATFORMIO_PROGRAM_LEDBOARD_STORE_INTERFACE_H