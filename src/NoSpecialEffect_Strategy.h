//
// Created by morgan on 5/15/2022.
//

#ifndef PLATFORMIO_PROGRAM_NOSPECIALEFFECT_STRATEGY_H
#define PLATFORMIO_PROGRAM_NOSPECIALEFFECT_STRATEGY_H

#include "SpecialEffects_Strategy.h"

class NoSpecialEffect_Strategy : public SpecialEffects_Strategy{
public:
    explicit NoSpecialEffect_Strategy(LedBoardsManager* context): SpecialEffects_Strategy(context){

    }

    void reset() override {

    }

    void updateValues(unsigned long currentTime) override {

    }

    void triggerOn(byte note, byte velocity) override {

    }

    void triggerOff(byte note, byte velocity) override {

    }


    void reinit() override {
        _fractionOfSpecialEffectToShow = 0;
        _specialEffectBaseColor = CRGB::Black;

    }

};

#endif //PLATFORMIO_PROGRAM_NOSPECIALEFFECT_STRATEGY_H