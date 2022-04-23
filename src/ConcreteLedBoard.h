//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_CONCRETELEDBOARD_H
#define GONZYPROJECT_CONCRETELEDBOARD_H

#include "ILedBoard.h"

class ConcreteLedBoard : public ILedBoard {
public:
    explicit ConcreteLedBoard();

    void init(CRGB* leds, uint8_t pixelPin, ILedBoardsManager* manager) override;

    void show() override;

    void command(LightCommands lightCommand) override;

    void update(unsigned long newTime) override;


    void setBoardColor(CRGB color) override;

private:
    ILedBoardsManager* _manager;
    CRGB* _leds{};
    CRGB _boardColor{0,80,0};
};

#endif //GONZYPROJECT_CONCRETELEDBOARD_H