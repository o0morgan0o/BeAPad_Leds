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

void FullLightStrategy::update() {
    _lifeSpan = _context->getCurrentTime() - _birthTime;
    for (uint8_t i = 0; i < _context->PixelCount; i++) {
        _boardLeds[i] = _crgbStrategyColor;
    }
}

void FullLightStrategy::trigger() {

}