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
    _numberOfTouchPins = 1;
    String message{"Number of touch Pins: "};
    message += _numberOfTouchPins;
    _debugHelper->add(message);
    // initialization of PinStateValidators
    for (uint8_t i = 0; i < _numberOfTouchPins; i++) {
        _pinStateValidators[i].init(&TOUCH_THRESHOLD, &RELEASE_THRESHOLD);
    }
//    for (uint8_t i = 0; i < _numberOfTouchPins; i++) {
//
//        // we set all states to released at start
//        _currentAboveTouchThreshold[i] = false;
//        _prevAboveTouchThreshold[i] = false;
//    }

}

void CapacitiveTouch_Dispatcher::connectBoardToCapacitiveSensor(uint8_t boardIndex, uint8_t capacitiveSensorIndex) {
    _boardIndexReferences[capacitiveSensorIndex] = boardIndex;
}

void CapacitiveTouch_Dispatcher::loop() {
    // VALUE WHEN TOUCH = 15 approximately
    // VALUE WHEN UNTOUCHED = 60 approximately

    for (uint8_t i = 0; i < _numberOfTouchPins; i++) {
        auto value = getTouchReadValueOnPin(_touchPins[i]);
        switch( _pinStateValidators[i].checkNewValue(value)){
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
    //
//        _debugHelper->add(String{value});
//        if (!_prevAboveTouchThreshold[i] && value < TOUCH_THRESHOLD) {
//            // if value was 0 and now we are below touch threshold
//            // it means we are at trigger ON
//            String message{"TOUCH PRESSED "};
//            message += value;
////                _debugHelper->add(message);
//            _currentAboveTouchThreshold[i] = true;
//            _midiHandler->sendMidiNoteOn();
//
//        } else if (_prevAboveTouchThreshold[i] && value > RELEASE_THRESHOLD) {
//            // if value was 1 and now we are abouve release threshold
//            // it means we are at trigger RELEASE
//            String message{"TOUCH RELEASED "};
//            message += value;
////                _debugHelper->add(message);
//            _currentAboveTouchThreshold[i] = false;
//        }
////            String message{"NO EVENT "};
////            message += value;
////            _debugHelper->add(message);
//        _prevAboveTouchThreshold[i] = _currentAboveTouchThreshold[i];
//    }


//        // Get the currently touched pads
//        currtouched = cap.touched();
//        _debugHelper->add(String{currtouched});
////        Serial.println(currtouched);
//        for (uint8_t i = 0; i < 12; i++) {
//            // it if *is* touched and *wasnt* touched before, alert!
//            if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
//                String message{"TOUCH DETECTED"};
//                message += i;
//                _debugHelper->add(message);
////                _manager->handleBoardTouched(_boardIndexReferences[i]);
//            }
//            // if it *was* touched and now *isnt*, alert!
//            if (!(currtouched & _BV(i)) && (lasttouched & _BV(i))) {
//                String message{"RELEASED DETECTED"};
//                message += i;
//                _debugHelper->add(message);
////                _manager->handleBoardReleased(_boardIndexReferences[i]);
//            }
//        }
//        // reset our state
//        lasttouched = currtouched;

}