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
        for (unsigned char &midiNote: _midiNotesToSend) {
            midiNote = UNDEFINED_NOTE;
        }
        for (unsigned char &midiNote: _shiftMidiNotesToSend) {
            midiNote = UNDEFINED_NOTE;
        }
        for (unsigned char &boardReference: _boardReferences) {
            boardReference = INACTIVE_BOARD;
        }

    }

    virtual void connectBoardToSendMidiKey(uint8_t touchPin, uint8_t board, uint8_t midiKey, uint8_t shiftMidiKey) {
        // We store at {pinIndex} location in the array, the corresponding midiKey to send
        _midiNotesToSend[touchPin] = midiKey;
        _shiftMidiNotesToSend[touchPin] = shiftMidiKey;
        _boardReferences[touchPin] = board;
    }

    virtual uint8_t getMidiKeyAssociatedWithPinIndex(uint8_t pinIndex) {
        return _midiNotesToSend[pinIndex];
    }
    virtual uint8_t getShiftMidiKeyAssociatedWithPinIndex(uint8_t pinIndex){
        return _shiftMidiNotesToSend[pinIndex];
    }

    virtual uint8_t getBoardAssociatedWithPinIndex(uint8_t pinIndex) {
        return _boardReferences[pinIndex];
    }

public:
    const uint8_t UNDEFINED_NOTE{100}; // arbitrary value for a pin without MidiKey Connected.
    const uint8_t INACTIVE_BOARD{100}; // arbitrary value for a board not Connected

protected:
    LedBoardsManager *_manager;
    Debug_Helper *_debugHelper;
    uint8_t _midiNotesToSend[128]{};
    uint8_t _shiftMidiNotesToSend[128]{};
    uint8_t _boardReferences[128]{};

};

#endif //PLATFORMIO_PROGRAM_MIDIKEYSENDER_H