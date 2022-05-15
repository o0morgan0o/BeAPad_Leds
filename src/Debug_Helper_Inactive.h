//
// Created by morgan on 4/30/2022.
//

#ifndef PLATFORMIO_PROGRAM_DEBUG_HELPER_INACTIVE_H
#define PLATFORMIO_PROGRAM_DEBUG_HELPER_INACTIVE_H

#include "Debug_Helper.h"


class Debug_Helper_Inactive : public Debug_Helper{
public:
    Debug_Helper_Inactive() : Debug_Helper(){

    }

    void add(const String &message) override {
    }

    void reinit() override {
    }

    void logWifiInit(const String &ip) override {
    }

    void logRTPMidiInit(const String &appleMidiName, const String &appleMidiPort) override {
    }

    void logMidiMessage(const String &note_type, byte channel, byte note, byte velocity) override {
    }

};

#endif //PLATFORMIO_PROGRAM_DEBUG_HELPER_INACTIVE_H