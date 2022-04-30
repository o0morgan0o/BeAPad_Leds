//
// Created by morgan on 5/1/2022.
//

#ifndef PLATFORMIO_PROGRAM_CAPACITIVETOUCH_DISPATCHER_H
#define PLATFORMIO_PROGRAM_CAPACITIVETOUCH_DISPATCHER_H

#include "Midi_Handler.h"

class CapacitiveTouch_Dispatcher {
public:
    CapacitiveTouch_Dispatcher(Midi_Handler* midiHandler, Debug_Helper * debugHelper);

    virtual void begin();

    virtual uint16_t getTouchReadValueOnPin(uint8_t pin)=0;

    virtual void loop();

    virtual void connectBoardToCapacitiveSensor(uint8_t boardIndex, uint8_t capacitiveSensorIndex);

private:
    uint8_t _numberOfTouchPins = 12;
    uint8_t _touchPins[12]{};
    bool _currentStates[12]{};
    bool _prevStates[12]{};
    //
    //
    uint8_t TOUCH_THRESHOLD = 25;
    uint8_t RELEASE_THRESHOLD = 40;
    //
    Midi_Handler *_midiHandler;
    Debug_Helper *_debugHelper;
    // Keeps track of the last pins touched
    // so we know when buttons are 'released'
    uint16_t lasttouched = 0;
    uint16_t currtouched = 0;
    //
    uint8_t _boardIndexReferences[128]{};
};

#endif //PLATFORMIO_PROGRAM_CAPACITIVETOUCH_DISPATCHER_H