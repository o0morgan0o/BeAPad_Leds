//
// Created by morgan on 5/14/2022.
//

#include "StromboscopeSpecialEffect_Strategy.h"
#include "LedBoardsManager.h"
#include "main_constants.h"

void StromboscopeSpecialEffect_Strategy::reset() {

}

void StromboscopeSpecialEffect_Strategy::updateValues(unsigned long currentTime) {
    if(!_isPlaying) return;
//    auto debugHelper = _context->getDebugHelper();
//    String message{"In update"};
//    message += _frameCounter;
//    debugHelper->add(message);
    _frameCounter += 1;
    if (_frameCounter >= NB_OF_FRAMES_PER_FLASH) {
        if (_isFlashing) {
            _isFlashing = false;
            _fractionOfSpecialEffectToShow = (uint8_t) INTENSITY_WHEN_OFF;
        } else {
            _isFlashing = true;
            _fractionOfSpecialEffectToShow = (uint8_t) INTENSITY_WHEN_ON;
        }
        _frameCounter = 0;
    }
//    _fractionOfSpecialEffectToShow-=1;
//    if(_fractionOfSpecialEffectToShow <=0){
//        _fractionOfSpecialEffectToShow = 0;
//    }

}

void StromboscopeSpecialEffect_Strategy::triggerOn(byte note, byte velocity) {
    INTENSITY_WHEN_ON = (int) velocity;
    _specialEffectBaseColor = CRGB(CHSV(
            (uint8_t) (note) * 2, // h
            SPECIAL_EFFECT_CHANNEL_COLOR_SATURATION, // s
            (uint8_t) (velocity) * 2) // v
                    );
    _isPlaying = true;
    _frameCounter = 0;
    _isFlashing = false;

}

void StromboscopeSpecialEffect_Strategy::triggerOff(byte note, byte velocity) {
    _isPlaying = false;
    _isFlashing = false;
    _fractionOfSpecialEffectToShow = INTENSITY_WHEN_OFF;

}

void StromboscopeSpecialEffect_Strategy::reinit() {
    _frameCounter = 0;

}