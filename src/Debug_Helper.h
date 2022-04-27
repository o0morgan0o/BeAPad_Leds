//
// Created by morgan on 4/23/2022.
//

#ifndef PLATFORMIO_PROGRAM_DEBUG_HELPER_H
#define PLATFORMIO_PROGRAM_DEBUG_HELPER_H
#ifdef IN_TESTING
#include "../test/FakeString.h"
using namespace std;
#else

#include <Arduino.h>

#endif

#include <cstring>
#include "LogMessages_Store.h"

class Debug_Helper {
public:
    String getString() {
        return _logString;
    }

    virtual void add(const String &message) {
        if(_logString.length() > 2000){ // I don't want too much log messages so reset if too big
            reinit();
        }
        _logString += message;
        _logString += "<br/>";
    }

    virtual void reinit() {
        _logString = "DEBUG_STRING<br/>";
    }

    void logWifiInit(const String& ip ){
        String logMessage{"WifiStarted"};
        logMessage += "IP address: ";
        logMessage += ip;
        add(logMessage);
    }

    void logRTPMidiInit(const String& appleMidiName, const String& appleMidiPort){
        String logMessage{"Adding RTP_MIDI "};
        logMessage += appleMidiName;
        logMessage += " PORT: ";
        logMessage += appleMidiPort;
        add(logMessage);

    }

    void logMidiMessage(const String &note_type, byte channel, byte note, byte velocity) {
        String logMessage{"RECEIVING MIDI "};
        logMessage += note_type;
        logMessage += " CHANNEL : ";
        logMessage += String{channel};
        logMessage += " NOTE : ";
        logMessage += String(note);
        logMessage += " VELOCITY : ";
        logMessage += String(velocity);
        add(logMessage);
    }

    void setDEBUGLights(bool newDebugState) {
        _debugFullLight = newDebugState;
    }


    bool getDebugFullLight() const {
        return _debugFullLight;
    }

private:
    bool _debugFullLight{false};
    String _logString{"DEBUG_STRING<br/>"};
};

#endif //PLATFORMIO_PROGRAM_DEBUG_HELPER_H