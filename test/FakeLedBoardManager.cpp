//
// Created by morgan on 4/25/2022.
//

#include "FakeLedBoardManager.h"

void FakeLedBoardManager::init() {
}

void FakeLedBoardManager::showGlobally(CRGB color) {
}

void FakeLedBoardManager::show() {
}

void FakeLedBoardManager::showQuickBlink(CRGB color) {
}

void FakeLedBoardManager::showBaseColor() {

}

LightStrategy_Factory *FakeLedBoardManager::getLightStrategyFactory() {
    return _lightStrategyFactory;
}