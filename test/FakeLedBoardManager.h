//
// Created by morgan on 4/25/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKELEDBOARDMANAGER_H
#define GONZY_PROJECT_TEST_FAKELEDBOARDMANAGER_H

#define IN_TESTING
#include "../src/LedBoardsManager.h"

class FakeLedBoardManager : public LedBoardsManager{
public:
    explicit FakeLedBoardManager(LedBoard_Store_Interface *store, LightStrategy_Factory* factory): LedBoardsManager(store, factory){
    }

    void showBaseColor() override;

    void init() override;

private:
    void show() override;

public:
    void showGlobally(CRGB color) override;

    LightStrategy_Factory* getLightStrategyFactory();

    void showQuickBlink(CRGB color) override;

};

#endif //GONZY_PROJECT_TEST_FAKELEDBOARDMANAGER_H