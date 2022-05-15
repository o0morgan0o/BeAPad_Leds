//
// Created by morgan on 5/14/2022.
//

#ifndef PLATFORMIO_PROGRAM_SPECIALEFFECT_FACTORY_H
#define PLATFORMIO_PROGRAM_SPECIALEFFECT_FACTORY_H

#include "SpecialEffects_Strategy.h"
#include "StromboscopeSpecialEffect_Strategy.h"

class LedBoardsManager;

class SpecialEffect_Factory {
public:
    SpecialEffect_Factory() = default;

    SpecialEffects_Strategy* makeStromboscopeSpecialEffect_Strategy(LedBoardsManager *context);;

    SpecialEffects_Strategy* makeNoSpecialEffect_Strategy(LedBoardsManager* context);

};

#endif //PLATFORMIO_PROGRAM_SPECIALEFFECT_FACTORY_H