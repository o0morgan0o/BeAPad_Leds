//
// Created by morgan on 5/13/2022.
//

#ifndef PLATFORMIO_PROGRAM_STRATEGYMIXER_H
#define PLATFORMIO_PROGRAM_STRATEGYMIXER_H

#ifdef IN_TESTING
#include "../test/Fake_CRGB.h"
#else
#include <FastLED.h>
#endif
#include "LightStrategy.h"

class StrategyMixer {
public:
    static CRGB mixStrategies(CRGB mainStrategyLedColor, CRGB shiftStrategyLedColor, bool isInShiftState) {
        if (!isInShiftState) {
            return mainStrategyLedColor;
        } else {
            // fract : 0 is the source color, 255 is the target color
            return blend(mainStrategyLedColor, shiftStrategyLedColor, 170);
        }

    }

};

#endif //PLATFORMIO_PROGRAM_STRATEGYMIXER_H