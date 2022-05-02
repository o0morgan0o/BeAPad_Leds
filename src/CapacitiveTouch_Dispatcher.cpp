//
// Created by morgan on 5/1/2022.
//

#include "CapacitiveTouch_Dispatcher.h"

CapacitiveTouch_Dispatcher::CapacitiveTouch_Dispatcher(Midi_Handler *midiHandler, Debug_Helper *debugHelper) {
    _midiHandler = midiHandler;
    _debugHelper = debugHelper;

}

void CapacitiveTouch_Dispatcher::begin() {
    _debugHelper->add("Touch Sensor Initialization");

    // defines attached pins
    _touchPins[0] = T0;
    _touchPins[1] = T2;
    _touchPins[2] = T3;
    _touchPins[3] = T4;
    _touchPins[4] = T5;
    _touchPins[5] = T6;
    _touchPins[6] = T7;
    _touchPins[7] = T8;
    _touchPins[8] = T9;
    //
    _numberOfTouchPins = 9;
    //
    String message{"Number of touch Pins: "};
    message += _numberOfTouchPins;
    _debugHelper->add(message);
    // initialization of PinStateValidators
    for (uint8_t i = 0; i < _numberOfTouchPins; i++) {
        _pinStateValidators[i].init(&TOUCH_THRESHOLD, &RELEASE_THRESHOLD);
    }
}

void CapacitiveTouch_Dispatcher::connectBoardToCapacitiveSensor(uint8_t boardIndex, uint8_t capacitiveSensorIndex) {
    _boardIndexReferences[capacitiveSensorIndex] = boardIndex;
}

void CapacitiveTouch_Dispatcher::loop() {
    // master change minor
    // VALUE WHEN TOUCH = 15 approximately
    // VALUE WHEN UNTOUCHED = 60 approximately

    for (uint8_t i = 0; i < _numberOfTouchPins; i++) {
        auto value = getTouchReadValueOnPin(_touchPins[i]);
        // FOR DEBUG
        _debugHelper->logTouchMessage(i, value);
        switch (_pinStateValidators[i].checkNewValue(value)) {
            case CapacitiveTouch_Actions::ACTION_TOUCH_VALIDATED:
                _midiHandler->sendMidiNoteOn();
                break;
            case CapacitiveTouch_Actions::ACTION_RELEASE_VALIDATED:
                _midiHandler->sendMidiNoteOff();
                break;
            case CapacitiveTouch_Actions::ACTION_STANDBY:
                break;
            default:
                break;
        }
    }

}