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

void FadeOutLightStrategy::update() {
    auto manager = _context->getManager();
    if (manager->getShiftState()) {
        for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
            _context->updateLedColorInBoard(i, manager->getShiftColor());
        }
    } else {
        _crgbStrategyColor.fadeToBlackBy(1);
        _lifeSpan = _context->getCurrentTime() - _birthTime;
        for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
            _context->updateLedColorInBoard(i, _crgbStrategyColor);
        }
    }

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