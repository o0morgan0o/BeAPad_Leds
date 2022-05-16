//
// Created by morgan on 5/15/2022.
//

#include "SerpentinLightStrategy.h"
#include "LedBoard.h"
#include "LedBoardsManager.h"

SerpentinLightStrategy::SerpentinLightStrategy(LedBoard *context) : LightStrategy(context) {
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _serpentinLeds[i] = SerpentinSingleLed();
        _serpentinLeds[i].setColors(_channelBaseColor, CRGB::Black);
        _serpentinLeds[i].setDelayBeforeStartAndLifeExpectancy(DELAY_BEFORE_EACH_LED * i, MAX_LIFE_EXPECTANCY);
    }
}

void SerpentinLightStrategy::reset() {

}

void SerpentinLightStrategy::updateValues(unsigned long currentTime) {
    _currentTime = currentTime;
    if (!_isActive) {
        return;
    }
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
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _serpentinLeds[i].forceDeath(_currentTime + DELAY_BEFORE_EACH_LED * i);
    }

}

void SerpentinLightStrategy::reinit(unsigned long currentTime) {
    // needed to have the correct time at the first trigger (after changeLightStrategy)
    _currentTime = currentTime;
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _serpentinLeds[i].setColors(_channelBaseColor, CRGB::Black);
    }
}