//
// Created by morgan on 5/12/2022.
//

#ifndef PLATFORMIO_PROGRAM_SHIFTKEYLIGHTSTRATEGY_H
#define PLATFORMIO_PROGRAM_SHIFTKEYLIGHTSTRATEGY_H

#include "LightStrategy.h"

class ShiftKeyLightStrategy : public LightStrategy {
public:
    explicit ShiftKeyLightStrategy(LedBoard *context);

    void reset() override;

    void updateValues(unsigned long currentTime) override;

    void triggerOn() override;

    void triggerOff() override;

    void reinit(unsigned long currentTime) override;

};

#endif //PLATFORMIO_PROGRAM_SHIFTKEYLIGHTSTRATEGY_H