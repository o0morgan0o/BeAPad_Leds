//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_CONCRETELEDBOARD_H
#define GONZYPROJECT_CONCRETELEDBOARD_H

#include <cstdint>
#include "ILedBoard.h"

class ConcreteLedBoard : public ILedBoard {
public:
    explicit ConcreteLedBoard();

    void init(CRGB* leds, uint8_t pixelPin) override;

    void show() override;

    void command(LightCommands lightCommand) override;

    void update(unsigned long newTime) override;

private:
//    RgbColor red{127, 100, 0};
//    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip{PixelCount, _pixelPin};

};

#endif //GONZYPROJECT_CONCRETELEDBOARD_H