//
// Created by morgan on 4/25/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKELEDBOARD_H
#define GONZY_PROJECT_TEST_FAKELEDBOARD_H
#define IN_TESTING

#include "../src/LedBoard.h"

class FakeLedBoard : public LedBoard {
public:
    explicit FakeLedBoard(LightStrategy_Factory *factory) : LedBoard(factory) {}

    void show() override {};

    LightStrategy_Factory* getLightStrategyFactory(){ return _lightStrategyFactory;}

    LightStrategy * getLightStrategy() { return _lightStrategy; }

};

#endif //GONZY_PROJECT_TEST_FAKELEDBOARD_H