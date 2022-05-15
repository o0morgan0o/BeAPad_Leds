//
// Created by morgan on 5/15/2022.
//

#ifndef PLATFORMIO_PROGRAM_SERPENTINSINGLELED_H
#define PLATFORMIO_PROGRAM_SERPENTINSINGLELED_H

#include <FastLED.h>

class SerpentinSingleLed {
public:
    explicit SerpentinSingleLed()= default;

    void setDelayBeforeStartAndLifeExpectancy(double delayBeforeStart, double lifeExpectancy){
        _delayBeforeStart = delayBeforeStart;
        _lifeExpectancy = lifeExpectancy;
    }

    void reborn(double time){
        _birthTime = time;
        _startTime = _birthTime + _delayBeforeStart;
    }


    CRGB getColorAtTime(double currentTime){
        if(currentTime >= _startTime && currentTime < _startTime+ _lifeExpectancy ){
            return _colorWhenOn;
        }else{
            return _colorWhenOff;
        }
    }

    void forceDeath(){
        _lifeExpectancy = 0;

    }

private:
    double _delayBeforeStart{0};
    double _lifeExpectancy{0};
    double _birthTime{0};
    double _startTime{0};

    CRGB _colorWhenOn{CRGB::Red};
    CRGB _colorWhenOff{CRGB::Black};

};

#endif //PLATFORMIO_PROGRAM_SERPENTINSINGLELED_H