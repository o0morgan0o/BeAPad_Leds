//
// Created by morgan on 5/2/2022.
//

#ifndef PLATFORMIO_PROGRAM_MIDIKEYSENDER_H
#define PLATFORMIO_PROGRAM_MIDIKEYSENDER_H

#include "LedBoardsManager.h"
#include "Debug_Helper.h"

class MidiKeySender {
public:
    MidiKeySender(LedBoardsManager *manager, Debug_Helper *debugHelper) {
        _manager = manager;
        _debugHelper = debugHelper;
        //
        // initialization of midiKeyReferences
        for (unsigned char &pinIndexReference: _pinIndexReferences) {
            pinIndexReference = INACTIVE_PIN;
        }

    }

    virtual void connectBoardToSendMidiKey(uint8_t pinIndex, uint8_t midiKey) {
        // We store at {pinIndex} location in the array, the corresponding midiKey to send
        _pinIndexReferences[pinIndex] = midiKey;
    }

    virtual uint8_t getMidiKeyAssociatedWithPinIndex(uint8_t pinIndex) {
        return _pinIndexReferences[pinIndex];
    }

public:
    const uint8_t INACTIVE_PIN{100}; // arbitrary value for a pin without MidiKey Connected.

protected:
    LedBoardsManager *_manager;
    Debug_Helper *_debugHelper;
    uint8_t _pinIndexReferences[128]{};

};

#endif //PLATFORMIO_PROGRAM_MIDIKEYSENDER_H