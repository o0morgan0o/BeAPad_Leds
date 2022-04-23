//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_ILEDBOARDSMANAGER_H
#define GONZYPROJECT_ILEDBOARDSMANAGER_H

#include "ILedBoard.h"
#include <vector>
#ifndef IN_TESTING
#include <FastLED.h>
#endif

class ILedBoardsManager {
public:
    explicit ILedBoardsManager(const std::vector<ILedBoard *> &ledBoards) {
        _ledBoards = ledBoards;
    }

    virtual void init() = 0;

    virtual void lightAll(uint8_t r, uint8_t g, uint8_t b) = 0;

    virtual void forceLightOff() = 0;

    virtual void show() = 0;

    virtual void update(unsigned long currentTime) = 0;

    virtual void setRandomColorForEachBoard() = 0;

    virtual const CRGB &getCurrentGlobalColor()  =0;

    virtual void showSuccessSignal() = 0;

    virtual void showErrorSignal() = 0;

protected:
    std::vector<ILedBoard *> _ledBoards;
    CRGB ledStrip1[9]{};
    CRGB ledStrip2[9]{};
    CRGB ledStrip3[9]{};
    CRGB ledStrip4[9]{};
    CRGB ledStrip5[9]{};
    CRGB ledStrip6[9]{};
    CRGB ledStrip7[9]{};
    CRGB ledStrip8[9]{};

};

#endif //GONZYPROJECT_ILEDBOARDSMANAGER_H