//
// Created by morgan on 4/25/2022.
//

#ifndef PLATFORMIO_PROGRAM_LIGHTSTRATEGY_H
#define PLATFORMIO_PROGRAM_LIGHTSTRATEGY_H

#ifdef IN_TESTING
#include "../test/Fake_CRGB.h"
#else
#include <FastLED.h>
#endif


class LedBoard;

class LightStrategy {

public:
    explicit LightStrategy(LedBoard* context, unsigned long lifeSpan);

    virtual void reset()= 0;


    virtual void update() =0;


protected:

    unsigned long _lifeSpan;
    unsigned long _currentLife{};
    unsigned long _birthTime{};
    CRGB _strategyColor;


    LedBoard* _context;


};

#endif //PLATFORMIO_PROGRAM_LIGHTSTRATEGY_H