//
// Created by morgan on 5/15/2022.
//

#ifndef PLATFORMIO_PROGRAM_SERPENTINLIGHTSTRATEGY_H
#define PLATFORMIO_PROGRAM_SERPENTINLIGHTSTRATEGY_H

#include "LightStrategy.h"
#include "SerpentinSingleLed.h"

class SerpentinLightStrategy : public LightStrategy {
public:
    explicit SerpentinLightStrategy(LedBoard* context);

    void reset() override;

    void updateValues(unsigned long currentTime) override;

    void triggerOn() override;

    void triggerOff() override;

    void reinit(unsigned long currentTime) override;

private:
    bool _isActive{false};
    unsigned long _currentTime{0};

    SerpentinSingleLed _serpentinLeds[MAX_NUMBER_OF_LEDS_PER_BOARD];
    unsigned long DELAY_BEFORE_EACH_LED = 40;
    unsigned long MAX_LIFE_EXPECTANCY = 4000;

};



#endif //PLATFORMIO_PROGRAM_SERPENTINLIGHTSTRATEGY_H