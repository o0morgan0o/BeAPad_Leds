//
// Created by morgan on 4/30/2022.
//

#include "Midi_Handler.h"

Midi_Handler::Midi_Handler(MidiKeyDispatcher *dispatcher, Debug_Helper *debugHelper) {
//
    _dispatcher = dispatcher;
    _debugHelper = debugHelper;
}


void Midi_Handler::handleConnected() {
    _debugHelper->add("RTP_MIDI Connected");
}

void Midi_Handler::handleDisconnected() {
    _debugHelper->add("ERROR !!! RTP_MIDI DisConnected !");

}

void Midi_Handler::handleOn(byte channel, byte note, byte velocity) {
    _debugHelper->logMidiMessage(String{"NOTE_ON"}, channel, note, velocity);
    _dispatcher->handleNoteOn(note);
}

void Midi_Handler::handleNoteOff(byte channel, byte note, byte velocity) {
    _debugHelper->logMidiMessage(String{"NOTE_OFF"}, channel, note, velocity);
//        _dispatcher->
}