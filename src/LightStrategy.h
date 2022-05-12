//
// Created by morgan on 4/25/2022.
//

#ifndef PLATFORMIO_PROGRAM_LIGHTSTRATEGY_H
#define PLATFORMIO_PROGRAM_LIGHTSTRATEGY_H

#include "RGB_Color.h"

#ifdef IN_TESTING
#include "../test/Fake_CRGB.h"
#else

#include <FastLED.h>

#endif

class LedBoard;

enum class LIGHT_STRATEGIES {
    NO_LIGHT_STRATEGY,
    STRATEGY_FULL_LIGHT,
    STRATEGY_FADE_OUT,
    STRATEGY_FADE_IN_AND_FADE_OUT,
    STRATEGY_SHIFT_KEY_STRATEGY

};

class LightStrategy {
public:
    explicit LightStrategy(LedBoard *context);

    virtual ~LightStrategy() =default;

    virtual void reset() = 0;

    virtual void update() = 0;

    virtual void triggerOn() = 0;

    virtual void triggerOff() = 0;

    virtual void reinit();

public:
    virtual unsigned long getLifeSpan() { return _lifeSpan; }

    virtual unsigned long getBirthTime() { return _birthTime; }

    virtual CRGB getStrategyColor() { return _crgbStrategyColor; }

protected:
    unsigned long _lifeSpan{};
    unsigned long _currentLife{};
    unsigned long _birthTime{};
    CRGB *_boardLeds{};
    CRGB _crgbStrategyColor{0, 0, 0};
    LedBoard *_context{};
    //
    bool isTouched = false;

};

#endif //PLATFORMIO_PROGRAM_LIGHTSTRATEGY_H