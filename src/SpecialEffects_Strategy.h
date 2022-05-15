//
// Created by morgan on 5/14/2022.
//

#ifndef PLATFORMIO_PROGRAM_SPECIALEFFECTS_STRATEGY_H
#define PLATFORMIO_PROGRAM_SPECIALEFFECTS_STRATEGY_H
#ifdef IN_TESTING
#include "../test/Fake_CRGB.h"
#else

#include <FastLED.h>

#endif

class LedBoardsManager;

enum class SPECIAL_EFFECT_STRATEGY {
    NO_SPECIAL_EFFECT,
    SPECIAL_EFFECT_STROMBOSCOPE
};

class SpecialEffects_Strategy {
public:
    explicit SpecialEffects_Strategy(LedBoardsManager *context);

    virtual ~SpecialEffects_Strategy() = default;

    virtual void reset() = 0;

    virtual void updateValues(unsigned long currentTime) = 0;

    virtual void triggerOn(byte note, byte velocity) = 0;

    virtual void triggerOff(byte note, byte velocity) = 0;

    virtual void reinit() = 0;

    virtual uint8_t getFractOfSpecialEffectToShow() {
        return _fractionOfSpecialEffectToShow;
    };

    virtual CRGB getSpecialEffectColor() {
        return _specialEffectColor;
    };
protected:
    CRGB _specialEffectColor{CRGB::White};
    int _fractionOfSpecialEffectToShow{0};
    LedBoardsManager *_context{};

};

#endif //PLATFORMIO_PROGRAM_SPECIALEFFECTS_STRATEGY_H