//
// Created by morgan on 5/13/2022.
//

#ifndef PLATFORMIO_PROGRAM_MAIN_CONSTANTS_H
#define PLATFORMIO_PROGRAM_MAIN_CONSTANTS_H
#endif //PLATFORMIO_PROGRAM_MAIN_CONSTANTS_H
#ifdef IN_TESTING
#else
#include <FastLED.h>
#endif

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

#define NO_MIDI_TRIGGER_FOR_BOARD 0
#define ONE_PARTICIPANT

// Project constants
#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_11_SHIFT_PIN 9
#define SPECIAL_EFFECT_CHANNEL_COLOR_SATURATION 200