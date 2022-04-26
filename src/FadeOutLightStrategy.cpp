//
// Created by morgan on 4/26/2022.
//

#include "FadeOutLightStrategy.h"
#include "LedBoard.h"

FadeOutLightStrategy::FadeOutLightStrategy(LedBoard *context) : LightStrategy(context){}

void FadeOutLightStrategy::reset() {
    _birthTime = _context->getCurrentTime();

    _crgbStrategyColor = CRGB{
            _context->getBoardBaseColor().r,
            _context->getBoardBaseColor().g,
            _context->getBoardBaseColor().b
    };
}

void FadeOutLightStrategy::update() {
    _crgbStrategyColor.fadeToBlackBy(1);
    _lifeSpan = _context->getCurrentTime() - _birthTime;
    for (uint8_t i = 0; i < _context->PixelCount; i++) {
        _boardLeds[i] = _crgbStrategyColor;
    }

}

void FadeOutLightStrategy::trigger() {
    _crgbStrategyColor = CRGB{
            _context->getBoardBaseColor().r,
            _context->getBoardBaseColor().g,
            _context->getBoardBaseColor().b
    };

}