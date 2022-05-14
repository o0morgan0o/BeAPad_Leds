
//
// Created by morgan on 4/25/2022.
//

#include "NoLightStrategy.h"
#include "LedBoard.h"

void NoLightStrategy::reset() {
    _crgbStrategyColor = CRGB::Black;
}

void NoLightStrategy::updateValues() {

}

void NoLightStrategy::triggerOn() {
    for(uint8_t i = 0; i <  _context->NUM_PIXELS; i++){
        _ledColorsInStrategy[i] = CRGB::Black;
    }

}

void NoLightStrategy::triggerOff() {


}

void NoLightStrategy::reinit() {
    _crgbStrategyColor = CRGB::Black;
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _ledColorsInStrategy[i] = CRGB::Black;
    }

}