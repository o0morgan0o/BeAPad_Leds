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

}

void ShiftKeyLightStrategy::triggerOn() {
    auto manager = _context->getManager();
    manager->setShiftState(true);
//    _crgbStrategyColor = manager->getShiftColor();

}

void ShiftKeyLightStrategy::triggerOff() {
    auto manager = _context->getManager();
    manager->setShiftState(false);
//    _crgbStrategyColor = CRGB::Black;
}