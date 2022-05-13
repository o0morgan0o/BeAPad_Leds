//
// Created by morgan on 4/30/2022.
//

#ifndef PLATFORMIO_PROGRAM_MIDI_HANDLER_H
#define PLATFORMIO_PROGRAM_MIDI_HANDLER_H

#include "LedBoardsManager.h"
#include "MidiKeyReceiver.h"
#include "MidiKeySender.h"
//

class Midi_Handler {
public:
    Midi_Handler(MidiKeyReceiver *receiver,MidiKeySender* sender, Debug_Helper *debugHelper);


    virtual void init() = 0;

    virtual void handleConnected();

    virtual void handleDisconnected();

    virtual void handleOn(byte channel, byte note, byte velocity);

    virtual void handleNoteOff(byte channel, byte note, byte velocity);

    virtual void sendMidiOnByTouchPin(uint8_t boardIndex, bool isInShiftState) = 0;

    virtual void sendMidiOffByTouchPin(uint8_t boardIndex, bool isInShiftState) = 0;

    virtual uint8_t getBoardAssociatedWithTouchPin(uint8_t touchPin);;

    virtual void loop() = 0;

public:
    String _midiSessionName{};
    uint16_t _midiPort{};
    //
    MidiKeyReceiver *_midiReceiver;
    MidiKeySender *_midiSender;
    Debug_Helper *_debugHelper;

};

#endif //PLATFORMIO_PROGRAM_MIDI_HANDLER_H