//
// Created by morgan on 4/26/2022.
//

#ifndef PLATFORMIO_PROGRAM_FADEOUTLIGHTSTRATEGY_H
#define PLATFORMIO_PROGRAM_FADEOUTLIGHTSTRATEGY_H

#include "LightStrategy.h"

class FadeOutLightStrategy : public LightStrategy {
public:
    explicit FadeOutLightStrategy(LedBoard *context);;

    void triggerOn() override;

    void reset() override;

    void updateValues(unsigned long currentTime) override;

    void triggerOff() override;

    void reinit(unsigned long currentTime) override;

};

#endif //PLATFORMIO_PROGRAM_FADEOUTLIGHTSTRATEGY_H