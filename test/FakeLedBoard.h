//
// Created by morgan on 4/25/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKELEDBOARD_H
#define GONZY_PROJECT_TEST_FAKELEDBOARD_H
#define IN_TESTING

#include "../src/LedBoard.h"

class FakeLedBoard : public LedBoard {
public:
    explicit FakeLedBoard(uint8_t pin, uint8_t nb_pixels, LightStrategy_Factory *factory) : LedBoard(pin, nb_pixels,factory) {}

    void showGlobalColor(CRGB color) override {

    }

    void showBaseColor() override {

    }

    void updateLedColorInBoard(uint8_t ledIndexInBoard, CRGB updatedColor) override {

    }

    void updateLedColorInBoard(uint8_t ledIndexInBoard, uint8_t r, uint8_t g, uint8_t b) override {

    }

    void show() override {};

    LightStrategy_Factory* getLightStrategyFactory(){ return _lightStrategyFactory;}

    LightStrategy * getLightStrategy() { return _lightStrategy; }

};

#endif //GONZY_PROJECT_TEST_FAKELEDBOARD_H