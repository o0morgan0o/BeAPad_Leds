//
// Created by morgan on 5/8/2022.
//

#ifndef PLATFORMIO_PROGRAM_CAPACITIVETOUCH_MPR121DISPATCHER_H
#define PLATFORMIO_PROGRAM_CAPACITIVETOUCH_MPR121DISPATCHER_H

#include "Midi_Handler.h"
#include "Debug_Helper.h"
#include "CapacitiveTouch_Dispatcher.h"
#include "Adafruit_MPR121.h"

class CapacitiveTouch_MPR121Dispatcher : public CapacitiveTouch_Dispatcher {
public:
    CapacitiveTouch_MPR121Dispatcher(LedBoardsManager *manager, Midi_Handler *midiHandler, Debug_Helper *debugHelper) :
            CapacitiveTouch_Dispatcher(manager, midiHandler, debugHelper) {
        _cap = new Adafruit_MPR121();
    }

    void begin() override {
        String mprConnectionResult{};
        // We don't block here after many tries
        uint8_t mprConnectionRetries = 0;
        uint8_t MAX_RETRIES = 5;
        while (!_cap->begin(0x5A)) {
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
        currtouched = _cap->touched();
        // Get the currently touched pads
        for (uint8_t i = 0; i < 12; i++) {
            // it if *is* touched and *wasnt* touched before, alert!
            if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
                _debugHelper->add(String{i});
                _debugHelper->add("touched");
                _midiHandler->sendMidiOnByTouchPin(i);
                auto boardToTrigger = _midiHandler->getBoardAssociatedWithTouchPin(i);
                _manager->triggerOnBoard(boardToTrigger);
            }
            // if it *was* touched and now *isnt*, alert!
            if (!(currtouched & _BV(i)) && (lasttouched & _BV(i))) {
                _debugHelper->add(String{i});
                _debugHelper->add("released");
                _midiHandler->sendMidiOffByTouchPin(i);
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
    Adafruit_MPR121 *_cap;
};

#endif //PLATFORMIO_PROGRAM_CAPACITIVETOUCH_MPR121DISPATCHER_H