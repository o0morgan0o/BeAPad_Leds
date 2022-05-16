//
// Created by morgan on 4/25/2022.
//

#include "FullLightStrategy.h"
#include "LedBoard.h"

FullLightStrategy::FullLightStrategy(LedBoard *context) : LightStrategy(context) {
}

void FullLightStrategy::reset() {
    _birthTime = _context->getCurrentTime();
}

void FullLightStrategy::updateValues(unsigned long currentTime) {
    _lifeSpan = _context->getCurrentTime() - _birthTime;
}

void FullLightStrategy::triggerOn() {
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _ledColorsInStrategy[i] = _channelBaseColor;
    }
}

void FullLightStrategy::triggerOff() {
    for(uint8_t i = 0 ; i < _context->NUM_PIXELS; i++){
        _ledColorsInStrategy[i] = CRGB::Black;
    }

}

void FullLightStrategy::reinit(unsigned long currentTime) {
    _birthTime = _context->getCurrentTime();
    //
}