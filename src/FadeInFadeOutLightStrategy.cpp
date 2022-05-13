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
    CRGB color = blend(CRGB::AliceBlue, CRGB::Red, fraction);
    _lifeSpan = _context->getCurrentTime() - _birthTime;
//    if (!isTouched) {
//        for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
////        _context->updateLedColorInBoard(i, random8(), random8(), random8());
//            _context->updateLedColorInBoard(i, color);
//        }
//    }else{
//        for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
////        _context->updateLedColorInBoard(i, random8(), random8(), random8());
//            _context->updateLedColorInBoard(i , 0 ,0 ,0);
//        }
//
//    }

}

void FadeInFadeOutLightStrategy::reinit() {
    _birthTime = _context->getCurrentTime();
    //
    _crgbStrategyColor = CRGB{
            _context->getBoardBaseColor().r,
            _context->getBoardBaseColor().g,
            _context->getBoardBaseColor().b
    };

}

void FadeInFadeOutLightStrategy::triggerOn() {
    isTouched = true;
    _currentLife = 0;
    fraction = 0;
    _crgbStrategyColor = CRGB{
            _context->getBoardBaseColor().r,
            _context->getBoardBaseColor().g,
            _context->getBoardBaseColor().b
    };

}

void FadeInFadeOutLightStrategy::triggerOff() {
    isTouched = false;

}