//
// Created by morgan on 5/12/2022.
//


#include "ShiftKeyLightStrategy.h"
#include "LedBoard.h"
#include  "LedBoardsManager.h"

ShiftKeyLightStrategy::ShiftKeyLightStrategy(LedBoard *context) : LightStrategy(context) {}

void ShiftKeyLightStrategy::reset() {

}

void ShiftKeyLightStrategy::updateValues(unsigned long currentTime) {
}

void ShiftKeyLightStrategy::reinit(unsigned long currentTime) {
    _birthTime = _context->getCurrentTime();
    //
    auto manager = _context->getManager();
    _channelBaseColor = manager->getShiftColor();
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _ledColorsInStrategy[i] = _channelBaseColor;
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