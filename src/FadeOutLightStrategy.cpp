//
// Created by morgan on 4/26/2022.
//

#include "FadeOutLightStrategy.h"
#include "LedBoard.h"
#include "LedBoardsManager.h"

FadeOutLightStrategy::FadeOutLightStrategy(LedBoard *context) : LightStrategy(context) {}

void FadeOutLightStrategy::reset() {
    _birthTime = _context->getCurrentTime();
    _crgbStrategyColor = CRGB{
            _context->getBoardBaseColor().r,
            _context->getBoardBaseColor().g,
            _context->getBoardBaseColor().b
    };
}

void FadeOutLightStrategy::updateValues() {
    _crgbStrategyColor.fadeToBlackBy(10);
    _lifeSpan = _context->getCurrentTime() - _birthTime;
}

void FadeOutLightStrategy::reinit() {
    _birthTime = _context->getCurrentTime();
    //
    _crgbStrategyColor = CRGB{
            _context->getBoardBaseColor().r,
            _context->getBoardBaseColor().g,
            _context->getBoardBaseColor().b
    };

}

void FadeOutLightStrategy::triggerOn() {
    _crgbStrategyColor = CRGB{
            _context->getBoardBaseColor().r,
            _context->getBoardBaseColor().g,
            _context->getBoardBaseColor().b
    };

}

void FadeOutLightStrategy::triggerOff() {

}