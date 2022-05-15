//
// Created by morgan on 5/15/2022.
//

#include "SerpentinLightStrategy.h"
#include "LedBoard.h"
#include "LedBoardsManager.h"

void SerpentinLightStrategy::reset() {

}

void SerpentinLightStrategy::updateValues(unsigned long currentTime) {
    _currentTime = currentTime;
    if (!_isActive) {
        return;
    }
//    auto debugHelper = _context->getManager()->getDebugHelper();
//    String message{" CURRENT_TIME: "};
//    message+= _currentTime;
//    message+= " ";
//    message += _serpentinLeds[0].getStartTime();
//    message += " ";
//    message += _serpentinLeds[0].getLifeExpectancy();
//    debugHelper->add(message);

    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _ledColorsInStrategy[i] = _serpentinLeds[i].getColorAtTime(_currentTime);
    }
}

void SerpentinLightStrategy::triggerOn() {
    _isActive = true;
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _serpentinLeds[i].reborn(_currentTime);
    }

}

void SerpentinLightStrategy::triggerOff() {
    _isActive = false;
    for(uint8_t i = 0 ; i < _context->NUM_PIXELS; i++){
        _serpentinLeds[i].forceDeath();
        _ledColorsInStrategy[i] = CRGB::Black;
    }

}

void SerpentinLightStrategy::reinit(unsigned long currentTime) {
    // needed to have the correct time at the first trigger (after changeLightStrategy)
    _currentTime = currentTime;

}

SerpentinLightStrategy::SerpentinLightStrategy(LedBoard *context) : LightStrategy(context) {
    double DELAY_BEFORE_EACH_LED = 40;
    double LIFE_EXPECTANCY = 300;
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _serpentinLeds[i] = SerpentinSingleLed();
        _serpentinLeds[i].setDelayBeforeStartAndLifeExpectancy(DELAY_BEFORE_EACH_LED * i, LIFE_EXPECTANCY);
    }

}