//
// Created by morgan on 4/26/2022.
//

#ifndef PLATFORMIO_PROGRAM_FADEOUTLIGHTSTRATEGY_H
#define PLATFORMIO_PROGRAM_FADEOUTLIGHTSTRATEGY_H

#include "LightStrategy.h"

class FadeOutLightStrategy : public LightStrategy{
public:
    void trigger() override;

    explicit FadeOutLightStrategy(LedBoard* context);;
    void reset() override;

    void update() override;

};

#endif //PLATFORMIO_PROGRAM_FADEOUTLIGHTSTRATEGY_H