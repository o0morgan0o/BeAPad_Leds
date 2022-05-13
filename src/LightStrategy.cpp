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
    _crgbStrategyColor = CRGB{
            _context->getBoardBaseColor().r,
            _context->getBoardBaseColor().g,
            _context->getBoardBaseColor().b
    };
    //
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _ledColorsInStrategy[i] = _crgbStrategyColor;
    }

}

CRGB LightStrategy::getStrategyColor() {
    return _crgbStrategyColor;
}

CRGB LightStrategy::getSpecificLedColor(uint8_t index) {
    return _ledColorsInStrategy[index];
}