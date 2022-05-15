//
// Created by morgan on 4/30/2022.
//

#include "Midi_Handler.h"

Midi_Handler::Midi_Handler(MidiKeyReceiver *receiver, MidiKeySender *sender, Debug_Helper *debugHelper) {
//
    _midiReceiver = receiver;
    _midiSender = sender;
    _debugHelper = debugHelper;
}

void Midi_Handler::handleConnected() {
    _debugHelper->add("RTP_MIDI Connected");
}

void Midi_Handler::handleDisconnected() {
    _debugHelper->add("ERROR !!! RTP_MIDI DisConnected !");

}

void Midi_Handler::handleOn(byte channel, byte note, byte velocity) {
    _debugHelper->logMidiMessage(String{"\n[<====] RECEIVING MIDI NOTE_ON"}, channel, note, velocity);
    _midiReceiver->handleNoteOn(channel, note);
}

void Midi_Handler::handleNoteOff(byte channel, byte note, byte velocity) {
    _debugHelper->logMidiMessage(String{"\n[<====] RECEIVING NOTE_OFF"}, channel, note, velocity);
    _midiReceiver->handleNoteOff(note);
}

void Midi_Handler::handleOnSpecialEffect(byte channel, byte note, byte velocity) {
    _debugHelper->logMidiMessage(String{"\n[<====] RECEIVING SPECIAL EFFECT NOTE_ON"}, channel, note, velocity);
    _midiReceiver->handleOnSpecialEffect(channel, note, velocity);

}

void Midi_Handler::handleOffSpecialEffect(byte channel, byte note, byte velocity) {
    _debugHelper->logMidiMessage(String{"\n[<====] RECEIVING SPECIAL EFFECT NOTE_OFF"}, channel, note, velocity);
    _midiReceiver->handleOffSpecialEffect(channel, note, velocity);

}

uint8_t Midi_Handler::getBoardAssociatedWithTouchPin(uint8_t touchPin) {
    return _midiSender->getBoardAssociatedWithPinIndex(touchPin);

}