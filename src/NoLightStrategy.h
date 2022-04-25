//
// Created by morgan on 4/25/2022.
//

#ifndef PLATFORMIO_PROGRAM_NOLIGHTSTRATEGY_H
#define PLATFORMIO_PROGRAM_NOLIGHTSTRATEGY_H

#include "LightStrategy.h"

class NoLightStrategy : public LightStrategy {
public:
    NoLightStrategy(LedBoard *context, unsigned long
    lifeSpan) : LightStrategy(context, lifeSpan) {}

    void reset() override;

    void update() override;
};

#endif //PLATFORMIO_PROGRAM_NOLIGHTSTRATEGY_H