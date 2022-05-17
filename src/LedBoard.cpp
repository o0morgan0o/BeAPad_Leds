//
// Created by morgan on 5/13/2022.
//

#include "LedBoard.h"
#include "LedBoardsManager.h"

LedBoard::LedBoard(uint8_t nb_pixels, LightStrategy_Factory *lightStrategyFactory) {
    NUM_PIXELS = nb_pixels;
    _lightStrategyFactory = lightStrategyFactory;
    _midiReceiveLightStrategy = _lightStrategyFactory->makeDefaultStrategy(this);
    _shiftLightStrategy = _lightStrategyFactory->makeDefaultShiftStrategy(this);
}

void LedBoard::giveReferenceManager(LedBoardsManager *manager) {
    _manager = manager;
}

LedBoardsManager *LedBoard::getManager() {
    return _manager;
}

void LedBoard::changeLightStrategy(LIGHT_STRATEGIES newStrategy) {
    // TODO remove debugger if not needed
    auto debugHelper = _manager->getDebugHelper();
    String message{"DEBUG: Changing Light Strategy : strategy Number "};
    message += (int) newStrategy;
    debugHelper->add(message);
    switch (newStrategy) {
        case LIGHT_STRATEGIES::NO_LIGHT_STRATEGY:
            delete _midiReceiveLightStrategy;
            _midiReceiveLightStrategy = _lightStrategyFactory->makeNoLightStrategy(this);
            break;
        case LIGHT_STRATEGIES::STRATEGY_FULL_LIGHT:
            delete _midiReceiveLightStrategy;
            _midiReceiveLightStrategy = _lightStrategyFactory->makeFullLightStrategy(this);
            break;
        case LIGHT_STRATEGIES::STRATEGY_FADE_OUT:
            delete _midiReceiveLightStrategy;
            _midiReceiveLightStrategy = _lightStrategyFactory->makeFadeOutLightStrategy(this);
            break;
        case LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT:
            delete _midiReceiveLightStrategy;
            _midiReceiveLightStrategy = _lightStrategyFactory->makeFadeInAndFadeOutLightStrategy(this);
            break;
        case LIGHT_STRATEGIES::STRATEGY_SERPENTIN:
            delete _midiReceiveLightStrategy;
            _midiReceiveLightStrategy = _lightStrategyFactory->makeSerpentinLightStrategy(this);
            break;
        case LIGHT_STRATEGIES::STRATEGY_FLASH_TOWARDS_EXTERIOR:
            delete _midiReceiveLightStrategy;
            _midiReceiveLightStrategy = _lightStrategyFactory->makeFlashTowardsExteriorStrategy(this);
            break;
        case LIGHT_STRATEGIES::STRATEGY_SHIFT_KEY_STRATEGY:
            delete _midiReceiveLightStrategy;
            _midiReceiveLightStrategy = _lightStrategyFactory->makeShiftKeyLightStrategy(this);
            break;
        default:
            debugHelper->add("ERROR ! Unknown light strategy");
            break;
    }
}

void LedBoard::reinitLightStrategy() {
    _midiReceiveLightStrategy->reinit(_currentTime);
    _shiftLightStrategy->reinit(_currentTime);
}

void LedBoard::triggerOn() {
    _midiReceiveLightStrategy->triggerOn();
}

void LedBoard::triggerOn(LIGHT_STRATEGIES strategy, CRGB color) {
    changeLightStrategy(strategy);
    _midiReceiveLightStrategy->setBaseColor(color);
    _midiReceiveLightStrategy->reinit(_currentTime);
    _midiReceiveLightStrategy->triggerOn();
}

void LedBoard::triggerOff() {
    if (_manager->getShiftState()) {
        _shiftLightStrategy->triggerOff();
        _midiReceiveLightStrategy->triggerOff();
    } else {
        _midiReceiveLightStrategy->triggerOff();
    }
}

void LedBoard::updateValues(unsigned long newTime) {
    _currentTime = newTime;
    _midiReceiveLightStrategy->updateValues(newTime);
    // TODO Check if the 2 updates don't delay anything.
    _shiftLightStrategy->updateValues(newTime);
}

void LedBoard::mixStrategies() {
    for (uint8_t i = 0; i < NUM_PIXELS; i++) {
        auto mixedColor = StrategyMixer::mixStrategies(
                _manager->getSpecialEffectStrategy(),
                _midiReceiveLightStrategy->getSpecificLedColor(i),
                _manager->getShiftColor(),
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