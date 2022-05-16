//
// Created by morgan on 5/14/2022.
//

#include "SpecialEffects_Strategy.h"
#include "LedBoardsManager.cpp"

SpecialEffects_Strategy::SpecialEffects_Strategy(LedBoardsManager *context) {
    _context = context;
}

uint8_t SpecialEffects_Strategy::getFractOfSpecialEffectToShow() {
    return _fractionOfSpecialEffectToShow;
}

CRGB &SpecialEffects_Strategy::getSpecialEffectColor() {
    return _specialEffectBaseColor;
}