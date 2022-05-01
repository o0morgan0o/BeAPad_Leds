//
// Created by morgan on 5/1/2022.
//

#ifndef PLATFORMIO_PROGRAM_CAPACITIVETOUCH_DISPATCHER_H
#define PLATFORMIO_PROGRAM_CAPACITIVETOUCH_DISPATCHER_H

#include "Midi_Handler.h"
#include "PinStateValidator.h"


class CapacitiveTouch_Dispatcher {
public:
    CapacitiveTouch_Dispatcher(Midi_Handler *midiHandler, Debug_Helper *debugHelper);

    virtual void begin();

    virtual uint16_t getTouchReadValueOnPin(uint8_t pin) = 0;

    virtual void loop();

    virtual void connectBoardToCapacitiveSensor(uint8_t boardIndex, uint8_t capacitiveSensorIndex);

    virtual void setTouchThreshold(uint8_t newThreshold) { TOUCH_THRESHOLD = newThreshold; }

    virtual void setReleaseThreashold(uint8_t newThreshold) { RELEASE_THRESHOLD = newThreshold; }

    uint8_t getTouchThreshold() const { return TOUCH_THRESHOLD; }

    uint8_t getReleaseThreashold() const { return RELEASE_THRESHOLD; }

private:
    uint8_t _numberOfTouchPins = 12;
    uint8_t _touchPins[12]{};

    PinStateValidator _pinStateValidators[12]{};

    bool _currentTouchThresholdActivated[12]{};
    bool _prevTouchThresholdActivated[12]{};
    bool _prevPrevTouchThresholdActivated[12]{};
    //
    bool _currentReleaseThresholdActivated[12]{};
    bool _prevReleaseThresholdActivated[12]{};
    bool _prevPrevReleaseThresholdActivated[12]{};

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