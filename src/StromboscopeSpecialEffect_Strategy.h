//
// Created by morgan on 5/14/2022.
//

#ifndef PLATFORMIO_PROGRAM_STROMBOSCOPESPECIALEFFECT_STRATEGY_H
#define PLATFORMIO_PROGRAM_STROMBOSCOPESPECIALEFFECT_STRATEGY_H

#include "SpecialEffects_Strategy.h"

class StromboscopeSpecialEffect_Strategy : public SpecialEffects_Strategy{
public:
    explicit StromboscopeSpecialEffect_Strategy(LedBoardsManager* context) : SpecialEffects_Strategy(context){

    }
    void reset() override;

    void updateValues(unsigned long currentTime) override;

    void triggerOn(byte note, byte velocity) override;

    void triggerOff(byte note, byte velocity) override;

    void reinit() override;

private:
    bool _isPlaying {false};
    int _frameCounter =0 ;
    bool _isFlashing{false};
    int INTENSITY_WHEN_ON = 100; // arbitrary value
    int INTENSITY_WHEN_OFF = 0;
    uint8_t NB_OF_FRAMES_PER_FLASH = 5; // the lower it is the more "electric" is the effect

};

#endif //PLATFORMIO_PROGRAM_STROMBOSCOPESPECIALEFFECT_STRATEGY_H