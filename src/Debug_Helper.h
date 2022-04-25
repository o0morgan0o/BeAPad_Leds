//
// Created by morgan on 4/23/2022.
//

#ifndef PLATFORMIO_PROGRAM_DEBUG_HELPER_H
#define PLATFORMIO_PROGRAM_DEBUG_HELPER_H
#ifdef IN_TESTING
#include "../test/FakeString.h"
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

    void add(const String &message) {
        _logString += message;
        _logString += "<br/>";
    }
    void reinit(){
        _logString="DEBUG_STRING<br/>";
    }

private:
    String _logString{"DEBUG_STRING<br/>"};
};

#endif //PLATFORMIO_PROGRAM_DEBUG_HELPER_H