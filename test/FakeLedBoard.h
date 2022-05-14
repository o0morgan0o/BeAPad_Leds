//
// Created by morgan on 4/25/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKELEDBOARD_H
#define GONZY_PROJECT_TEST_FAKELEDBOARD_H
#define IN_TESTING

#include "../src/LedBoard.h"

class FakeLedBoard : public LedBoard {
public:
    explicit FakeLedBoard(uint8_t nb_pixels, LightStrategy_Factory *factory);

    void initBoard() override;

    void showGlobalColor(CRGB color) override {

    }

    void showBaseColor() override {

    }

    void updateLedColorInBoard(uint8_t ledIndexInBoard, CRGB updatedColor) override {

    }

    void updateLedColorInBoard(uint8_t ledIndexInBoard, uint8_t r, uint8_t g, uint8_t b) override {

    }

    void show() override {};

    LightStrategy_Factory *getLightStrategyFactory() { return _lightStrategyFactory; }

    LightStrategy *getMainLightStrategy() { return _midiReceiveLightStrategy; }

};

#endif //GONZY_PROJECT_TEST_FAKELEDBOARD_H