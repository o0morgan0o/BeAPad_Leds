//
// Created by morgan on 4/25/2022.
//

#include "FullLightStrategy.h"
#include "LedBoard.h"

void FullLightStrategy::reset() {
    _strategyColor = 0xFF0000;

}

void FullLightStrategy::update() {
    _lifeSpan = _context->_currentTime - _birthTime;
//    _strategyColor.fadeToBlackBy(1);
    for (uint8_t i = 0; i < _context->PixelCount; i++) {
            _context->_leds[i] = _strategyColor;

//        if (random(0, 10) > 8.0)
//            _context->_leds[i] = _strategyColor;
//        else {
//            _context->_leds[i] = CRGB::Black;
//        }
    }
}