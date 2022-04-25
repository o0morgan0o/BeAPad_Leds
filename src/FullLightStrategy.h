//
// Created by morgan on 4/25/2022.
//

#ifndef PLATFORMIO_PROGRAM_FULLLIGHTSTRATEGY_H
#define PLATFORMIO_PROGRAM_FULLLIGHTSTRATEGY_H

#include "LightStrategy.h"

class FullLightStrategy: public LightStrategy {
public:
    FullLightStrategy(LedBoard* context, unsigned long lifeSpan) : LightStrategy(context, lifeSpan){


    }
    void reset() override;

    void update() override;

};

#endif //PLATFORMIO_PROGRAM_FULLLIGHTSTRATEGY_H