//
// Created by morgan on 4/25/2022.
//

#include "LightStrategy.h"
#include "LedBoard.h"

LightStrategy::LightStrategy(LedBoard *context) {
    _context = context;
    _context->getBoardLeds();
    //
    _birthTime = _context->getCurrentTime();
    //
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _ledColorsInStrategy[i] = _channelBaseColor;
    }
}



CRGB LightStrategy::getBaseColor() {
    return _channelBaseColor;
}

CRGB LightStrategy::getSpecificLedColor(uint8_t index) {
    return _ledColorsInStrategy[index];
}

void LightStrategy::setBaseColor(CRGB color) {
    _channelBaseColor = color;

}