//
// Created by morgan on 4/25/2022.
//

#ifndef PLATFORMIO_PROGRAM_NOLIGHTSTRATEGY_H
#define PLATFORMIO_PROGRAM_NOLIGHTSTRATEGY_H

#include "LightStrategy.h"

class NoLightStrategy : public LightStrategy {
public:
    explicit NoLightStrategy(LedBoard *context) : LightStrategy(context) {}

    void triggerOn() override;

    void reset() override;

    void update() override;

    void triggerOff() override;
};

#endif //PLATFORMIO_PROGRAM_NOLIGHTSTRATEGY_H