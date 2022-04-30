//
// Created by morgan on 4/30/2022.
//

#ifndef PLATFORMIO_PROGRAM_MIDI_HANDLER_H
#define PLATFORMIO_PROGRAM_MIDI_HANDLER_H

#include "LedBoardsManager.h"
#include "MidiKeyDispatcher.h"

#define ONE_PARTICIPANT
//
#include <Wire.h>
#include <ESPmDNS.h>
#include <AppleMidi.h>
#include <WiFiUdp.h>

class Midi_Handler {
public:
    Midi_Handler( MidiKeyDispatcher *dispatcher, Debug_Helper *debugHelper,
                 MidiInterface<appleMidi::AppleMIDISession<WiFiUDP>, appleMidi::AppleMIDISettings> *_midiSession,
                 appleMidi::AppleMIDISession<WiFiUDP> *_appleMidi
    );

    virtual void connected(const APPLEMIDI_NAMESPACE::ssrc_t &ssrc, const char *name) {

    }

    virtual void init();

    virtual void handleConnected();

    virtual void handleDisconnected();

    virtual void handleOn(byte channel, byte note, byte velocity);

    virtual void handleNoteOff(byte channel, byte note, byte velocity);

    virtual void sendMidiNoteOn();

    MidiInterface<appleMidi::AppleMIDISession<WiFiUDP>, appleMidi::AppleMIDISettings> *getMidiSession() const {
        return _midiSession;
    };

    appleMidi::AppleMIDISession<WiFiUDP> *getAppleMidi() const {
        return _appleMidi;
    };

    virtual void loop();

public:
    String _midiSessionName;
    uint16_t _midiPort;
    //
    MidiInterface<appleMidi::AppleMIDISession<WiFiUDP>, appleMidi::AppleMIDISettings> *_midiSession;
    appleMidi::AppleMIDISession<WiFiUDP> *_appleMidi;
    //
    MidiKeyDispatcher *_dispatcher;
    Debug_Helper *_debugHelper;

};

#endif //PLATFORMIO_PROGRAM_MIDI_HANDLER_H