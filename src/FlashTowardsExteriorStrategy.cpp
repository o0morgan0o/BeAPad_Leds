//
// Created by morgan on 5/16/2022.
//

#include "FlashTowardsExteriorStrategy.h"
#include "LedBoard.h"

FlashTowardsExteriorStrategy::FlashTowardsExteriorStrategy(LedBoard *context) : LightStrategy(context){
    unsigned long DELAY_BEFORE_EACH_LED = 40;
    unsigned long LIFE_EXPECTANCY = 300;
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _serpentinLeds[i] = SerpentinSingleLed();
    }
    // CUSTOM ORDER TO HAVE THE EFFECT OF A FLASH TOWARDS EXTERIOR
    _serpentinLeds[6].setDelayBeforeStartAndLifeExpectancy(DELAY_BEFORE_EACH_LED * 0, LIFE_EXPECTANCY);
    _serpentinLeds[0].setDelayBeforeStartAndLifeExpectancy(DELAY_BEFORE_EACH_LED * 1, LIFE_EXPECTANCY);
    _serpentinLeds[5].setDelayBeforeStartAndLifeExpectancy(DELAY_BEFORE_EACH_LED * 1, LIFE_EXPECTANCY);
    _serpentinLeds[7].setDelayBeforeStartAndLifeExpectancy(DELAY_BEFORE_EACH_LED * 2, LIFE_EXPECTANCY);
    _serpentinLeds[1].setDelayBeforeStartAndLifeExpectancy(DELAY_BEFORE_EACH_LED * 3, LIFE_EXPECTANCY);
    _serpentinLeds[4].setDelayBeforeStartAndLifeExpectancy(DELAY_BEFORE_EACH_LED * 3, LIFE_EXPECTANCY);
    _serpentinLeds[8].setDelayBeforeStartAndLifeExpectancy(DELAY_BEFORE_EACH_LED * 4, LIFE_EXPECTANCY);
    _serpentinLeds[2].setDelayBeforeStartAndLifeExpectancy(DELAY_BEFORE_EACH_LED * 5, LIFE_EXPECTANCY);
    _serpentinLeds[3].setDelayBeforeStartAndLifeExpectancy(DELAY_BEFORE_EACH_LED * 5, LIFE_EXPECTANCY);

}

void FlashTowardsExteriorStrategy::reset() {

}

void FlashTowardsExteriorStrategy::updateValues(unsigned long currentTime) {
    _currentTime = currentTime;
    if (!_isActive) {
        return;
    }
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _ledColorsInStrategy[i] = _serpentinLeds[i].getColorAtTime(_currentTime);
    }
}

void FlashTowardsExteriorStrategy::triggerOn() {
    _isActive = true;
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _serpentinLeds[i].reborn(_currentTime);
    }

}

void FlashTowardsExteriorStrategy::triggerOff() {
    _isActive = false;
    for (uint8_t i = 0; i < _context->NUM_PIXELS; i++) {
        _serpentinLeds[i].forceDeath(_currentTime);
        _ledColorsInStrategy[i] = CRGB::Black;
    }

}

void FlashTowardsExteriorStrategy::reinit(unsigned long currentTime) {
    // needed to have the correct time at the first trigger (after changeLightStrategy)
    _currentTime = currentTime;

}