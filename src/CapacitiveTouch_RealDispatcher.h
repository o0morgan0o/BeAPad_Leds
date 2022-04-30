//
// Created by morgan on 4/30/2022.
//

#ifndef PLATFORMIO_PROGRAM_CAPACITIVETOUCH_REALDISPATCHER_H
#define PLATFORMIO_PROGRAM_CAPACITIVETOUCH_REALDISPATCHER_H

#include "LedBoardsManager.h"
#include "Debug_Helper.h"
#include "Midi_Handler.h"
#include "CapacitiveTouch_Dispatcher.h"

class CapacitiveTouch_RealDispatcher : public CapacitiveTouch_Dispatcher {
public:
    CapacitiveTouch_RealDispatcher(Midi_Handler *midiHandler, Debug_Helper *debugHelper);

    uint16_t getTouchReadValueOnPin(uint8_t pin) override {
        return touchRead(pin);
    }

};

#endif //PLATFORMIO_PROGRAM_CAPACITIVETOUCH_REALDISPATCHER_H