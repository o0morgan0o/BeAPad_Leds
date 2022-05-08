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
        // TODO don't block here make many tries and show signal if no touch connection
        if (!_cap->begin(0x5A)) {
            mprConnectionResult += "ERROR ! MPR Connection Failed";
            while (1);
        }
        mprConnectionResult += "MPR Connection Success";
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

    void connectBoardToCapacitiveSensor(uint8_t boardIndex, uint8_t capacitiveSensorIndex) override {

    }

    void setTouchThreshold(uint8_t newThreshold) override {

    }

    void setReleaseThreashold(uint8_t newThreshold) override {

    }

    uint8_t getTouchThreshold() const override {
        return 0;
    }

    uint8_t getReleaseThreashold() const override {
        return 0;
    }

// Keeps track of the last pins touched
// so we know when buttons are 'released'
    uint16_t lasttouched = 0;
    uint16_t currtouched = 0;
    Adafruit_MPR121 *_cap;
};

#endif //PLATFORMIO_PROGRAM_CAPACITIVETOUCH_MPR121DISPATCHER_H