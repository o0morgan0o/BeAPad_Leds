//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_ILEDBOARD_H
#define GONZYPROJECT_ILEDBOARD_H

#include <cstdint>
#include "LightCommands.h"

#ifndef IN_TESTING
#include <FastLED.h>
#endif

class ILedBoardsManager;

class ILedBoard {
public:
    explicit ILedBoard() {
        _previousTime = 0.0;
    }

    virtual void init(CRGB *leds, uint8_t pixelPin, ILedBoardsManager* manager) = 0;

    virtual void show() = 0;

    virtual void command(LightCommands lightCommand) = 0;

    virtual void update(unsigned long newTime) = 0;

    virtual void setBoardColor(CRGB color) = 0;

protected:
    bool isOn = false;
    const uint16_t PixelCount = 9; // 9 leds per board
    unsigned long _previousTime;
    CRGB boardColor{};
    uint8_t _pixelPin{}; // we keep information of pixelPin just for debugInfo
};

#endif //GONZYPROJECT_ILEDBOARD_H