//
// Created by morgan on 5/16/2022.
//

#ifndef PLATFORMIO_PROGRAM_FLASHTOWARDSEXTERIORSTRATEGY_H
#define PLATFORMIO_PROGRAM_FLASHTOWARDSEXTERIORSTRATEGY_H

#include "LightStrategy.h"
#include "SerpentinSingleLed.h"

class FlashTowardsExteriorStrategy : public LightStrategy {
public:
    explicit FlashTowardsExteriorStrategy(LedBoard *context);

    void reset() override;

    void updateValues(unsigned long currentTime) override;

    void triggerOn() override;

    void triggerOff() override;

    void reinit(unsigned long currentTime) override;

private:
    bool _isActive{false};
    unsigned long _currentTime{0};
    SerpentinSingleLed _serpentinLeds[MAX_NUMBER_OF_LEDS_PER_BOARD];
};

#endif //PLATFORMIO_PROGRAM_FLASHTOWARDSEXTERIORSTRATEGY_H