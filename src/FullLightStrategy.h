//
// Created by morgan on 4/25/2022.
//

#ifndef PLATFORMIO_PROGRAM_FULLLIGHTSTRATEGY_H
#define PLATFORMIO_PROGRAM_FULLLIGHTSTRATEGY_H

#include "LightStrategy.h"

class FullLightStrategy : public LightStrategy {
public:
    explicit FullLightStrategy(LedBoard *context);

    void triggerOn() override;

    void reset() override;

    void updateValues() override;

    void reinit() override;

    void triggerOff() override;

};

#endif //PLATFORMIO_PROGRAM_FULLLIGHTSTRATEGY_H