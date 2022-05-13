//
// Created by morgan on 5/12/2022.
//


#include "ShiftKeyLightStrategy.h"
#include "LedBoard.h"
#include  "LedBoardsManager.h"

ShiftKeyLightStrategy::ShiftKeyLightStrategy(LedBoard *context) : LightStrategy(context) {}

void ShiftKeyLightStrategy::reset() {

}

void ShiftKeyLightStrategy::updateValues() {
}

void ShiftKeyLightStrategy::reinit() {
    _birthTime = _context->getCurrentTime();
    //
    _crgbStrategyColor = CRGB::Blue;
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _ledColorsInStrategy[i] = _crgbStrategyColor;
    }

}

void ShiftKeyLightStrategy::triggerOn() {
//    auto manager = _context->getManager();
//    manager->setShiftState(true);

}

void ShiftKeyLightStrategy::triggerOff() {
//    auto manager = _context->getManager();
//    manager->setShiftState(false);
}