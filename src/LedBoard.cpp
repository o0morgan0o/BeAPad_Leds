//
// Created by morgan on 5/13/2022.
//

#include "LedBoard.h"
#include "LedBoardsManager.h"

LedBoard::LedBoard(uint8_t nb_pixels, LightStrategy_Factory *lightStrategyFactory) {
    NUM_PIXELS = nb_pixels;
    _lightStrategyFactory = lightStrategyFactory;
    _mainLightStrategy = _lightStrategyFactory->makeDefaultStrategy(this);
    _shiftLightStrategy = _lightStrategyFactory->makeDefaultShiftStrategy(this);
}

void LedBoard::giveReferenceManager(LedBoardsManager *manager) {
    _manager = manager;
}

LedBoardsManager *LedBoard::getManager() {
    return _manager;
}

void LedBoard::changeLightStrategy(LIGHT_STRATEGIES newStrategy) {
    switch (newStrategy) {
        case LIGHT_STRATEGIES::NO_LIGHT_STRATEGY:
            delete _mainLightStrategy;
            _mainLightStrategy = _lightStrategyFactory->makeNoLightStrategy(this);
            break;
        case LIGHT_STRATEGIES::STRATEGY_FULL_LIGHT:
            delete _mainLightStrategy;
            _mainLightStrategy = _lightStrategyFactory->makeFullLightStrategy(this);
            break;
        case LIGHT_STRATEGIES::STRATEGY_FADE_OUT:
            delete _mainLightStrategy;
            _mainLightStrategy = _lightStrategyFactory->makeFadeOutLightStrategy(this);
            break;
        case LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT:
            delete _mainLightStrategy;
            _mainLightStrategy = _lightStrategyFactory->makeFadeInAndFadeOutLightStrategy(this);
            break;
        case LIGHT_STRATEGIES::STRATEGY_SHIFT_KEY_STRATEGY:
            delete _mainLightStrategy;
            _mainLightStrategy = _lightStrategyFactory->makeShiftKeyLightStrategy(this);
            break;
        default:
            break;

    }

}

void LedBoard::reinitLightStrategy() {
    _mainLightStrategy->reinit();
    _shiftLightStrategy->reinit();
}

void LedBoard::triggerOn() {
        _mainLightStrategy->triggerOn();
}

void LedBoard::triggerOff() {
    if (_manager->getShiftState()) {
        _shiftLightStrategy->triggerOff();
    } else {
        _mainLightStrategy->triggerOff();
    }
}

void LedBoard::updateValues(unsigned long newTime) {
    _currentTime = newTime;
    _mainLightStrategy->updateValues();
    // TODO Check if the 2 updates don't delay anything.
    _shiftLightStrategy->updateValues();
}

void LedBoard::mixStrategies() {
    // TODO implements strategy per pixel
    for (uint8_t i = 0; i < NUM_PIXELS; i++) {
        auto mixedColor = StrategyMixer::mixStrategies(
                _mainLightStrategy->getSpecificLedColor(i),
                _shiftLightStrategy->getSpecificLedColor(i),
                _manager->getShiftState());
        updateLedColorInBoard(i, mixedColor);
    }
}

void LedBoard::setBoardColor(uint8_t r, uint8_t g, uint8_t b) {
    _boardBaseColor.r = r;
    _boardBaseColor.g = g;
    _boardBaseColor.b = b;
}

void LedBoard::setBoardColor(CRGB color) {
    _boardBaseColor.r = color.r;
    _boardBaseColor.g = color.g;
    _boardBaseColor.b = color.b;
}

unsigned long LedBoard::getCurrentTime() { return _currentTime; }

CRGB *LedBoard::getBoardLeds() { return _leds; }

RGB_Color LedBoard::getBoardBaseColor() { return _boardBaseColor; }