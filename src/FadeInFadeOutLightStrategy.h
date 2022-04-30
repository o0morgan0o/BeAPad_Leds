//
// Created by morgan on 4/27/2022.
//

#ifndef PLATFORMIO_PROGRAM_FADEINFADEOUTLIGHTSTRATEGY_H
#define PLATFORMIO_PROGRAM_FADEINFADEOUTLIGHTSTRATEGY_H


#include "LightStrategy.h"

class FadeInFadeOutLightStrategy : public LightStrategy {
public:
    FadeInFadeOutLightStrategy(LedBoard *context) : LightStrategy(context) {}

    void reset() override;

    void update() override;

    void trigger() override;

    uint8_t fraction = 0;

};

#endif //PLATFORMIO_PROGRAM_FADEINFADEOUTLIGHTSTRATEGY_H