//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_CONCRETELEDBOARD_H
#define GONZYPROJECT_CONCRETELEDBOARD_H

#include "LedBoard.h"
#include "IBoardLeds.h"

class FastLedLedBoard : public LedBoard {
public:
    explicit FastLedLedBoard(uint8_t pin, uint8_t nb_pixels, LightStrategy_Factory *lightStrategyFactory):
            LedBoard(pin, nb_pixels, lightStrategyFactory){};

    void show() override{};

private:
};

#endif //GONZYPROJECT_CONCRETELEDBOARD_H