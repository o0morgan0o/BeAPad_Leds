//
// Created by morgan on 5/15/2022.
//

#ifndef PLATFORMIO_PROGRAM_SERPENTINSINGLELED_H
#define PLATFORMIO_PROGRAM_SERPENTINSINGLELED_H
#ifdef IN_TESTING
#include "../test/Fake_CRGB.h"
#else

#include <FastLED.h>

#endif

class SerpentinSingleLed {
public:
    explicit SerpentinSingleLed() = default;

    void setDelayBeforeStartAndLifeExpectancy(double delayBeforeStart, double lifeExpectancy) {
        _delayBeforeStart = delayBeforeStart;
        _initialLifeExpectancy = lifeExpectancy;
    }

    void reborn(unsigned long time) {
        _birthTime = time;
        _startTime = _birthTime + _delayBeforeStart;
        _lifeExpectancy = _initialLifeExpectancy;
    }

    CRGB getColorAtTime(unsigned long currentTime) const {
        if (getIsInLifeSpan(currentTime))
            return _colorWhenOn;
        else {
            return _colorWhenOff;
        }
    }

    bool getIsInLifeSpan(unsigned long currentTime) const {
        if (currentTime >= _startTime && currentTime < _startTime + _lifeExpectancy) {
            return true;
        } else {
            return false;
        }

    }

    void forceDeath() {
        _lifeExpectancy = 0;
    }

    double getDelayBeforeStart() const {
        return _delayBeforeStart;
    }

    double getLifeExpectancy() const {
        return _lifeExpectancy;
    }

    double getStartTime() const {
        return _startTime;
    }

public:
    CRGB _colorWhenOn{CRGB::FireBrick};
    CRGB _colorWhenOff{CRGB::Black};
private:
    unsigned long _delayBeforeStart{0};
    unsigned long _initialLifeExpectancy{0};
    unsigned long _lifeExpectancy{0};
    unsigned long _birthTime{0};
    unsigned long _startTime{0};

};

#endif //PLATFORMIO_PROGRAM_SERPENTINSINGLELED_H