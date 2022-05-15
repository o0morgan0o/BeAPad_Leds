//
// Created by morgan on 4/25/2022.
//

#ifndef PLATFORMIO_PROGRAM_LIGHTSTRATEGY_FACTORY_H
#define PLATFORMIO_PROGRAM_LIGHTSTRATEGY_FACTORY_H

#include "LightStrategy.h"
#include "NoLightStrategy.h"
#include "FullLightStrategy.h"
#include "FadeOutLightStrategy.h"
#include "FadeInFadeOutLightStrategy.h"
#include "ShiftKeyLightStrategy.h"
#include "SerpentinLightStrategy.h"

class LightStrategy_Factory {
public:
    LightStrategy_Factory() = default;

    LightStrategy *makeDefaultStrategy(LedBoard *context) {
        return makeNoLightStrategy(context);
    }

    LightStrategy *makeDefaultShiftStrategy(LedBoard *context) {
        return makeShiftKeyLightStrategy(context);
    }

    LightStrategy *makeNoLightStrategy(LedBoard *context) {
        return new NoLightStrategy(context);
    }

    LightStrategy *makeFullLightStrategy(LedBoard *context) {
        return new FullLightStrategy(context);
    }

    LightStrategy *makeFadeOutLightStrategy(LedBoard *context) {
        return new FadeOutLightStrategy(context);
    }

    LightStrategy *makeFadeInAndFadeOutLightStrategy(LedBoard *context) {
        return new FadeInFadeOutLightStrategy(context);
    }

    LightStrategy *makeSerpentinLightStrategy(LedBoard *context){
        return new SerpentinLightStrategy(context);
    }

    LightStrategy *makeShiftKeyLightStrategy(LedBoard *context) {
        return new ShiftKeyLightStrategy(context);
    }


};

#endif //PLATFORMIO_PROGRAM_LIGHTSTRATEGY_FACTORY_H