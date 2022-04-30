//
// Created by morgan on 4/30/2022.
//

#ifndef PLATFORMIO_PROGRAM_DEBUG_HELPER_SERIAL_H
#define PLATFORMIO_PROGRAM_DEBUG_HELPER_SERIAL_H

#include "Debug_Helper.h"

class Debug_Helper_Serial : public Debug_Helper {

public:
    Debug_Helper_Serial() : Debug_Helper(){
        Serial.begin(115200);

    }

    void add(const String &message) override {
        Serial.println(message);
    }

    void reinit() override {
    }

    void logWifiInit(const String &ip) override {
        Serial.println(ip);
    }

    void logRTPMidiInit(const String &appleMidiName, const String &appleMidiPort) override {
        String message{"RTP MIDI_INIT"};
        message+= appleMidiName;
        message+= " PORT: ";
        message+= appleMidiPort;
        Serial.println(message);
    }

    void logMidiMessage(const String &note_type, byte channel, byte note, byte velocity) override {
        Serial.println("MidiMESSAGE :");
        String message{note_type};
        message+= " Channel: ";
        message += channel;
        message+= " Note: ";
        message+= note;
        message += " Velocity: ";
        message+= velocity;
        Serial.println(message);
    }

};

#endif //PLATFORMIO_PROGRAM_DEBUG_HELPER_SERIAL_H