//
// Created by morgan on 5/8/2022.
//

#ifndef PLATFORMIO_PROGRAM_CAPACITIVETOUCH_DISPATCHER_H
#define PLATFORMIO_PROGRAM_CAPACITIVETOUCH_DISPATCHER_H

#include "Midi_Handler.h"
#include "Debug_Helper.h"
#include "ICapacitiveTouch_Dispatcher.h"
#include "Capacitive_Sensor.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

class CapacitiveTouch_Dispatcher : public ICapacitiveTouch_Dispatcher {
public:
    CapacitiveTouch_Dispatcher(LedBoardsManager *manager, Midi_Handler *midiHandler, Debug_Helper *debugHelper, Capacitive_Sensor *touchSensor) :
            ICapacitiveTouch_Dispatcher(manager, midiHandler, debugHelper) {
        _touchSensor = touchSensor;
        _touchSensor->create();

    }

    void begin() override {
        String mprConnectionResult{};
        // We don't block here after many tries
        uint8_t mprConnectionRetries = 0;
        uint8_t MAX_RETRIES = 5;
        while (!_touchSensor->begin()) {
            mprConnectionRetries++;
            mprConnectionResult += "ERROR ! MPR Connection Failed";
            mprConnectionResult += "Retrying in 2 second...";
            delay(2000);
            if (mprConnectionRetries >= MAX_RETRIES) {
                mprConnectionResult += "ERROR : Still no connection with MPR21, resume anyway ...";
                // Because of many errors, to show the user we produce a special blink signal on all leds
                _manager->showBlinkHighPriorityMessage(BlinkHighPriorityMessages::MPR121_SENSOR_NOT_FOUND);
                break;
            }
        }
        mprConnectionResult += "MPR Connection check done";
        _debugHelper->add(mprConnectionResult);
    }

    void loop() override {
        currtouched = _touchSensor->getTouched();
        // Get the currently touched pads
        for (uint8_t i = 0; i < 12; i++) {
            // it if *is* touched and *wasnt* touched before, alert!
            if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
                String message{i};
                message += " touched";
                _debugHelper->add(message);
                _midiHandler->sendMidiOnByTouchPin(i, _manager->getShiftState());
                auto boardToTrigger = _midiHandler->getBoardAssociatedWithTouchPin(i);
                _manager->triggerOnBoard(boardToTrigger);
            }
            // if it *was* touched and now *isnt*, alert!
            if (!(currtouched & _BV(i)) && (lasttouched & _BV(i))) {
                String message{i};
                message += " released";
                _debugHelper->add(message);
                _midiHandler->sendMidiOffByTouchPin(i, _manager->getShiftState());
                auto boardToTrigger = _midiHandler->getBoardAssociatedWithTouchPin(i);
                _manager->triggerOffBoard(boardToTrigger);
            }
        }
        // reset our state
        lasttouched = currtouched;
    }

    void setTouchThreshold(uint8_t newThreshold) override {

    }

    void setReleaseThreshold(uint8_t newThreshold) override {

    }

    uint8_t getTouchThreshold() const override {
        return 0;
    }

    uint8_t getReleaseThreshold() const override {
        return 0;
    }

// Keeps track of the last pins touched
// so we know when buttons are 'released'
    uint16_t lasttouched = 0;
    uint16_t currtouched = 0;
    Capacitive_Sensor *_touchSensor;
};

#endif //PLATFORMIO_PROGRAM_CAPACITIVETOUCH_DISPATCHER_H