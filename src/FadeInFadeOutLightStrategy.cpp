//
// Created by morgan on 4/27/2022.
//

#include "FadeInFadeOutLightStrategy.h"
#include "LedBoard.h"

void FadeInFadeOutLightStrategy::reset() {
    _birthTime = _context->getCurrentTime();
    _currentLife = 0;
    fraction = 0;
    _crgbStrategyColor = CRGB{
            _context->getBoardBaseColor().r,
            _context->getBoardBaseColor().g,
            _context->getBoardBaseColor().b
    };

}

void FadeInFadeOutLightStrategy::updateValues() {
    fraction += 1;
    CRGB newColor = blend(CRGB::AliceBlue, CRGB::Red, fraction);
    _lifeSpan = _context->getCurrentTime() - _birthTime;
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _ledColorsInStrategy[i] = newColor;
    }
}

void FadeInFadeOutLightStrategy::reinit() {
    fraction = 0;
    _birthTime = _context->getCurrentTime();
    //
    _crgbStrategyColor = CRGB{
            _context->getBoardBaseColor().r,
            _context->getBoardBaseColor().g,
            _context->getBoardBaseColor().b
    };

}

void FadeInFadeOutLightStrategy::triggerOn() {
    fraction = 0;
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _ledColorsInStrategy[i] = _crgbStrategyColor;
    }
}

void FadeInFadeOutLightStrategy::triggerOff() {
    isTouched = false;

}