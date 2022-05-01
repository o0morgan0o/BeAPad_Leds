//
// Created by morgan on 4/30/2022.
//

#ifndef PLATFORMIO_PROGRAM_MIDI_HANDLER_H
#define PLATFORMIO_PROGRAM_MIDI_HANDLER_H

#include "LedBoardsManager.h"
#include "MidiKeyDispatcher.h"
//

class Midi_Handler {
public:
    Midi_Handler( MidiKeyDispatcher *dispatcher, Debug_Helper *debugHelper);


    virtual void init() = 0;

    virtual void handleConnected();

    virtual void handleDisconnected();

    virtual void handleOn(byte channel, byte note, byte velocity);

    virtual void handleNoteOff(byte channel, byte note, byte velocity);

    virtual void sendMidiNoteOn() =0 ;

    virtual void sendMidiNoteOff() = 0;


    virtual void loop() = 0;

public:
    String _midiSessionName{};
    uint16_t _midiPort{};
    //
    MidiKeyDispatcher *_dispatcher;
    Debug_Helper *_debugHelper;

};

#endif //PLATFORMIO_PROGRAM_MIDI_HANDLER_H