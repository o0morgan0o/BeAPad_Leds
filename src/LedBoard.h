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
    explicit LedBoard(LightStrategy_Factory *lightStrategyFactory) {
        _lightStrategyFactory = lightStrategyFactory;
        _lightStrategy = _lightStrategyFactory->makeDefaultStrategy(this);
    }

    virtual void giveReferenceManager(CRGB *leds, uint8_t pixelPin, LedBoardsManager *manager) {
        _leds = leds;
        _manager = manager;
        _pixelPin = pixelPin;
    }

    virtual void changeLightStrategy(LIGHT_STRATEGIES newStrategy) {
        switch (newStrategy) {
            case LIGHT_STRATEGIES::NO_LIGHT_STRATEGY:
                delete _lightStrategy;
                _lightStrategy =_lightStrategyFactory->makeNoLightStrategy(this);
                break;
            case LIGHT_STRATEGIES::STRATEGY_FULL_LIGHT:
                delete _lightStrategy;
                _lightStrategy = _lightStrategyFactory->makeFullLightStrategy(this);
                break;
            case LIGHT_STRATEGIES::STRATEGY_FADE_OUT:
                delete _lightStrategy;
                _lightStrategy= _lightStrategyFactory->makeFadeOutLightStrategy(this);
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

    virtual void show() = 0;

    virtual void command(LightCommands lightCommand) {
        switch (lightCommand) {
            case LightCommands::LIGHT_ON: {
//                auto newBoardColor = _manager->getCurrentGlobalColor();
//                setBoardColor(newBoardColor);
                for (uint8_t i = 0; i < PixelCount; i++) {
//                    _leds[i] = _boardBaseColor;
                    _leds[i].setRGB(_boardBaseColor.r, _boardBaseColor.g, _boardBaseColor.b);
//                    = _boardBaseColor;
//                    _leds[i] = 0x00FF88;
                }
                break;
            }
            case LightCommands::LIGHT_OFF: {
                for (uint8_t i = 0; i < PixelCount; i++) {
                    _leds[i] = CRGB::Black;
                }
                break;
            }
            case LightCommands::LIGHT_SUCCESS: {
                for (uint8_t i = 0; i < PixelCount; i++) {
                    _leds[i] = CRGB::Green;
                }
                break;
            }
            case LightCommands::LIGHT_ERROR: {
                for (uint8_t i = 0; i < PixelCount; i++) {
                    _leds[i] = CRGB::Red;
                }
                break;
            }
            case LightCommands::LIGHT_WHITE: {
                for (uint8_t i = 0; i < PixelCount; i++) {
                    _leds[i] = CRGB::White;
                }
                break;
            }
            default:
                // should not be here
                break;

        }

    };

    virtual void trigger(){
        _lightStrategy->trigger();
    }

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

public:
    CRGB *_leds{};
    RGB_Color _boardBaseColor{100, 0, 0};
    unsigned long _currentTime{0};
    const uint16_t PixelCount = 9; // 9 leds per board
protected:
    LightStrategy_Factory *_lightStrategyFactory;
    LightStrategy *_lightStrategy;
protected:
    bool isOn = false;

    uint8_t _pixelPin{}; // we keep information of pixelPin just for debugInfo
    LedBoardsManager *_manager{};

};

#endif //GONZYPROJECT_ILEDBOARD_H