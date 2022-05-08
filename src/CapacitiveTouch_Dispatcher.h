//
// Created by morgan on 5/1/2022.
//

#ifndef PLATFORMIO_PROGRAM_CAPACITIVETOUCH_DISPATCHER_H
#define PLATFORMIO_PROGRAM_CAPACITIVETOUCH_DISPATCHER_H

#include "Midi_Handler.h"
#include "PinStateValidator.h"

class CapacitiveTouch_Dispatcher {
public:
    CapacitiveTouch_Dispatcher(LedBoardsManager *manager, Midi_Handler *midiHandler, Debug_Helper *debugHelper) {
        _manager = manager;
        _midiHandler = midiHandler;
        _debugHelper = debugHelper;
    }

    virtual void begin() = 0;

    virtual void loop() = 0;

    virtual void setTouchThreshold(uint8_t newThreshold) = 0;

    virtual void setReleaseThreshold(uint8_t newThreshold) = 0;

    virtual uint8_t getTouchThreshold() const = 0;

    virtual uint8_t getReleaseThreshold() const = 0;

protected:
    uint8_t _numberOfTouchPins = 12;
    uint8_t _touchPins[12]{};

    PinStateValidator _pinStateValidators[12]{};
    //
    uint8_t TOUCH_THRESHOLD = 35;
    uint8_t RELEASE_THRESHOLD = 40;
    //
    Midi_Handler *_midiHandler;
    LedBoardsManager *_manager;
    Debug_Helper *_debugHelper;
    // Keeps track of the last pins touched
    // so we know when buttons are 'released'
    uint16_t lasttouched = 0;
    uint16_t currtouched = 0;
    //
    uint8_t _boardIndexReferences[128]{};
};

#endif //PLATFORMIO_PROGRAM_CAPACITIVETOUCH_DISPATCHER_H