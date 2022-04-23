//
// Created by morgan on 4/23/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKEBOARD_H
#define GONZY_PROJECT_TEST_FAKEBOARD_H

#define IN_TESTING
#include "Fake_CRGB.h"

#include "../src/ILedBoard.h"


class FakeBoard : public ILedBoard {
public:
    void init(CRGB *leds, uint8_t pixelPin) override;

    void show() override;

    void command(LightCommands lightCommand) override;

    void update(unsigned long newTime) override;
};

#endif //GONZY_PROJECT_TEST_FAKEBOARD_H