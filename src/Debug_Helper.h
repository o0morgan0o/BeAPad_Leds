//
// Created by morgan on 4/23/2022.
//

#ifndef PLATFORMIO_PROGRAM_DEBUG_HELPER_H
#define PLATFORMIO_PROGRAM_DEBUG_HELPER_H
#include <Arduino.h>

class Debug_Helper {

private:
    static String _debugString;

public:
    static String getString(){
        return _debugString;
    }

    static void add(const String& message){
        _debugString += message;
        _debugString += "<br/>";
    }

};

#endif //PLATFORMIO_PROGRAM_DEBUG_HELPER_H