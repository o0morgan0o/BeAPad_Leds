//
// Created by morgan on 5/1/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKE_MIDIHANDLER_H
#define GONZY_PROJECT_TEST_FAKE_MIDIHANDLER_H

#define IN_TESTING
#include "../src/Midi_Handler.h"

class Fake_MidiHandler  : public Midi_Handler{
public:
    Fake_MidiHandler(MidiKeyDispatcher *dispatcher, Debug_Helper *debugHelper): Midi_Handler(dispatcher, debugHelper){

    }

    void init() override {

    }

    void sendMidiNoteOn() override {

    }

    void sendMidiNoteOff() override {

    }

    void loop() override {

    }

};

#endif //GONZY_PROJECT_TEST_FAKE_MIDIHANDLER_H