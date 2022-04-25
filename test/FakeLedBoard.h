//
// Created by morgan on 4/25/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKELEDBOARD_H
#define GONZY_PROJECT_TEST_FAKELEDBOARD_H

#define IN_TESTING
#include "../src/LedBoard.h"

class FakeLedBoard : public LedBoard{
public:
    void show() override{};

};

#endif //GONZY_PROJECT_TEST_FAKELEDBOARD_H