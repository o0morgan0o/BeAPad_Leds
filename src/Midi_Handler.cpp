//
// Created by morgan on 4/30/2022.
//

#include "Midi_Handler.h"

Midi_Handler::Midi_Handler( MidiKeyDispatcher *dispatcher, Debug_Helper *debugHelper,
                           MidiInterface<appleMidi::AppleMIDISession<WiFiUDP>, appleMidi::AppleMIDISettings> *midiSession,
                           appleMidi::AppleMIDISession<WiFiUDP> *appleMidi

) {
//    APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE();
_midiSession = midiSession;
_appleMidi = appleMidi;
//
_dispatcher = dispatcher;
_debugHelper = debugHelper;
_midiSessionName = appleMidi->getName();
_midiPort = appleMidi->getPort();
}

void Midi_Handler::sendMidiNoteOn() {
    _midiSession->sendNoteOn(60, 120, 1);
}

void Midi_Handler::loop() {
    _midiSession->read();
}

void Midi_Handler::init() {
//    if (!MDNS.begin(AppleMIDI.getName()))
    if (!MDNS.begin("AppleMIDI-ESP32"))
        _debugHelper->add("Error setting up MDNS responded !");
    _debugHelper->logRTPMidiInit("AppleMIDI-ESP32", String{_midiPort});
    MDNS.addService("apple-midi", "udp", _midiPort);
    _midiSession->begin(MIDI_CHANNEL_OMNI);
}

void Midi_Handler::handleConnected() {
    _debugHelper->add("RTP_MIDI Connected");
}

void Midi_Handler::handleDisconnected() {
    _debugHelper->add("ERROR !!! RTP_MIDI DisConnected !");

}

void Midi_Handler::handleOn(byte channel, byte note, byte velocity) {
    _debugHelper->logMidiMessage("NOTE_ON", channel, note, velocity);
    _dispatcher->handleNoteOn(note);
}

void Midi_Handler::handleNoteOff(byte channel, byte note, byte velocity) {
    _debugHelper->logMidiMessage("NOTE_OFF", channel, note, velocity);
//        _dispatcher->
}