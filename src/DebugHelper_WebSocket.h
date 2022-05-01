//
// Created by morgan on 5/1/2022.
//

#ifndef PLATFORMIO_PROGRAM_DEBUGHELPER_WEBSOCKET_H
#define PLATFORMIO_PROGRAM_DEBUGHELPER_WEBSOCKET_H

#include "Debug_Helper.h"
//
#include <ArduinoWebsockets.h>

class DebugHelper_WebSocket: public Debug_Helper {
public:
    DebugHelper_WebSocket(): Debug_Helper(){
        // ***************************
        // WEBSOCKET SERVER
        _wsServer.listen(8000);
        _wsClient = _wsServer.accept();

    }

    void add(const String &message) override {
        _logString += message;
        if (_wsClient.available()) {
            _wsClient.send(_logString);
            reinit();
        }
    }

    void add(const char *message) override {
        add(String{message});
    }

    void reinit() override {
        _logString = String{};
//        Debug_Helper::reinit();
    }

    void logWifiInit(const String &ip) override {
        Debug_Helper::logWifiInit(ip);
    }

    void logRTPMidiInit(const String &appleMidiName, const String &appleMidiPort) override {
        Debug_Helper::logRTPMidiInit(appleMidiName, appleMidiPort);
    }

    void logMidiMessage(const String &note_type, byte channel, byte note, byte velocity) override {
        Debug_Helper::logMidiMessage(note_type, channel, note, velocity);
    }

    websockets::WebsocketsServer _wsServer;
    websockets::WebsocketsClient _wsClient;
};

#endif //PLATFORMIO_PROGRAM_DEBUGHELPER_WEBSOCKET_H