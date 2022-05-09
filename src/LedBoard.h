//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_ILEDBOARD_H
#define GONZYPROJECT_ILEDBOARD_H

#include <cstdint>
#include "LightCommands.h"
#include "IBoardLeds.h"
#include "LightStrategy.h"
#include "FullLightStrategy.h"
#include "NoLightStrategy.h"
#include "RGB_Color.h"
#include "LightStrategy_Factory.h"

class LedBoardsManager;

#ifdef IN_TESTING
#include "../test/Fake_CRGB.h"
#else

#include <FastLED.h>

#endif

class LedBoard {
public:
    explicit LedBoard(uint8_t pin, uint8_t nb_pixels, LightStrategy_Factory *lightStrategyFactory) {
        _pin = pin;
        NUM_PIXELS = nb_pixels;
        _lightStrategyFactory = lightStrategyFactory;
        _lightStrategy = _lightStrategyFactory->makeDefaultStrategy(this);
    }

    virtual void giveReferenceManager(CRGB *leds, LedBoardsManager *manager) {
        _leds = leds;
        _manager = manager;
    }

    virtual void changeLightStrategy(LIGHT_STRATEGIES newStrategy) {
        switch (newStrategy) {
            case LIGHT_STRATEGIES::NO_LIGHT_STRATEGY:
                delete _lightStrategy;
                _lightStrategy = _lightStrategyFactory->makeNoLightStrategy(this);
                break;
            case LIGHT_STRATEGIES::STRATEGY_FULL_LIGHT:
                delete _lightStrategy;
                _lightStrategy = _lightStrategyFactory->makeFullLightStrategy(this);
                break;
            case LIGHT_STRATEGIES::STRATEGY_FADE_OUT:
                delete _lightStrategy;
                _lightStrategy = _lightStrategyFactory->makeFadeOutLightStrategy(this);
                break;
            case LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT:
                delete _lightStrategy;
                _lightStrategy = _lightStrategyFactory->makeFadeInAndFadeOutLightStrategy(this);
                break;
            default:
                break;

        }

    }

    virtual void reinitLightStrategy() {
        _lightStrategy->reinit();
    }

    virtual void showBaseColor() = 0;

    /**
     * This should be used only for display high-priority messages (like error messages)
     * @param color
     */
    virtual void showGlobalColor(CRGB color) = 0;

    virtual void show() = 0;;

    virtual void triggerOn() {
        _lightStrategy->triggerOn();
    }

    virtual void triggerOff() {
        _lightStrategy->triggerOff();
    }

    virtual void updateLedColorInBoard(uint8_t ledIndexInBoard, CRGB updatedColor) = 0;

    virtual void updateLedColorInBoard(uint8_t ledIndexInBoard, uint8_t r, uint8_t g, uint8_t b) = 0;

    virtual void update(unsigned long newTime) {
        _currentTime = newTime;
        _lightStrategy->update();
    };

    virtual void setBoardColor(uint8_t r, uint8_t g, uint8_t b) {
//        _boardBaseColor.setRGB(r,g,b);
        _boardBaseColor.r = r;
        _boardBaseColor.g = g;
        _boardBaseColor.b = b;
    };

    virtual void setBoardColor(CRGB color) {
        _boardBaseColor.r = color.r;
        _boardBaseColor.g = color.g;
        _boardBaseColor.b = color.b;
    };

    virtual unsigned long getCurrentTime() { return _currentTime; }

    virtual CRGB *getBoardLeds() { return _leds; }

    virtual RGB_Color getBoardBaseColor() { return _boardBaseColor; }

    virtual void initBoard() {}

    uint8_t NUM_PIXELS;
public:
    CRGB *_leds{};
    RGB_Color _boardBaseColor{255, 255, 0};
    unsigned long _currentTime{0};
protected:
    LightStrategy_Factory *_lightStrategyFactory;
    LightStrategy *_lightStrategy;
protected:
    uint8_t _pin{};
    bool isOn = false;
    LedBoardsManager *_manager{};

};

#endif //GONZYPROJECT_ILEDBOARD_H