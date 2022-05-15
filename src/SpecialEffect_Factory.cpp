//
// Created by morgan on 5/14/2022.
//

#include "SpecialEffect_Factory.h"
#include "LedBoardsManager.h"
#include "NoSpecialEffect_Strategy.h"

SpecialEffects_Strategy *SpecialEffect_Factory::makeStromboscopeSpecialEffect_Strategy(LedBoardsManager *context) {
    return new StromboscopeSpecialEffect_Strategy(context);
}

SpecialEffects_Strategy *SpecialEffect_Factory::makeNoSpecialEffect_Strategy(LedBoardsManager *context) {
   return new NoSpecialEffect_Strategy(context);
}