//
// Created by morgan on 5/1/2022.
//

#ifndef PLATFORMIO_PROGRAM_RTP_MIDI_MIDIHANDLER_H
#define PLATFORMIO_PROGRAM_RTP_MIDI_MIDIHANDLER_H

#include "main_constants.h"
#include "Midi_Handler.h"
#include <AppleMidi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <ESPmDNS.h>

class RTP_Midi_MidiHandler : public Midi_Handler {
public:
    RTP_Midi_MidiHandler(MidiKeyReceiver *receiver,
                         MidiKeySender *sender,
                         Debug_Helper *debugHelper,
                         MidiInterface<appleMidi::AppleMIDISession<WiFiUDP>, appleMidi::AppleMIDISettings> *midiSession,
                         appleMidi::AppleMIDISession<WiFiUDP> *appleMidi
    ) : Midi_Handler(receiver, sender, debugHelper) {
        //    APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE();
        _midiSession = midiSession;
        _appleMidi = appleMidi;
        _midiSessionName = appleMidi->getName();
        _midiPort = appleMidi->getPort();

    }

    void sendMidiOnByTouchPin(uint8_t touchPin, bool isInShiftState) override {
        uint8_t midiNoteToSend;
        if (isInShiftState) {
            midiNoteToSend = _midiSender->getShiftMidiKeyAssociatedWithPinIndex(touchPin);
        } else {
            midiNoteToSend = _midiSender->getMidiKeyAssociatedWithPinIndex(touchPin);
        }
        // TODO Disable debug if in release mode
        String message{"=> MIDI NOTE_ON: "};
        message += midiNoteToSend;
        _debugHelper->add(message);
        _midiSession->sendNoteOn(midiNoteToSend, 120, 1);
    }

    void sendMidiOffByTouchPin(uint8_t touchPin, bool isInShiftState) override {
        uint8_t midiNoteToSend;
        if (isInShiftState) {
            midiNoteToSend = _midiSender->getShiftMidiKeyAssociatedWithPinIndex(touchPin);
        } else {
            midiNoteToSend = _midiSender->getMidiKeyAssociatedWithPinIndex(touchPin);
        }
        // TODO Disable debug if in release mode
        String message{"=> MIDI NOTE_OFF: "};
        message += midiNoteToSend;
        _debugHelper->add(message);
        _midiSession->sendNoteOff(midiNoteToSend, 120, 1);
    }

    void init() override {
        if (!MDNS.begin("AppleMIDI-ESP32"))
            _debugHelper->add("Error setting up MDNS responded !");
        _debugHelper->logRTPMidiInit("AppleMIDI-ESP32", String{_midiPort});
        MDNS.addService("apple-midi", "udp", _midiPort);
        _midiSession->begin(MIDI_CHANNEL_OMNI);
    }

    void loop() override {
        _midiSession->read();
    }

    MidiInterface<appleMidi::AppleMIDISession<WiFiUDP>, appleMidi::AppleMIDISettings> *getMidiSession() const {
        return _midiSession;
    };

    appleMidi::AppleMIDISession<WiFiUDP> *getAppleMidi() const {
        return _appleMidi;
    };
private:
    MidiInterface<appleMidi::AppleMIDISession<WiFiUDP>, appleMidi::AppleMIDISettings> *_midiSession;
    appleMidi::AppleMIDISession<WiFiUDP> *_appleMidi;
};

#endif //PLATFORMIO_PROGRAM_RTP_MIDI_MIDIHANDLER_H