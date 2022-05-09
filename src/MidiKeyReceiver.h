//
// Created by morgan on 4/27/2022.
//

#ifndef PLATFORMIO_PROGRAM_MIDIKEYRECEIVER_H
#define PLATFORMIO_PROGRAM_MIDIKEYRECEIVER_H

#include "LedBoardsManager.h"
#include "Debug_Helper.h"

enum class MIDI_NOTE_TYPE {
    MIDI_NOTE_ON, MIDI_NOTE_OFF
};

/**
 * This class handle the midiEvents and pass it to the Board.
 *
 */
class MidiKeyReceiver {
public:
    MidiKeyReceiver(LedBoardsManager *manager, Debug_Helper *debugHelper) {
        _manager = manager;
        _debugHelper = debugHelper;

        // initialization of boardIndexReferences
        for (unsigned char &_boardIndexReference: _boardIndexReferences) {
            _boardIndexReference = INACTIVE_BOARD_INDEX;
        }
    }

    virtual void connectBoardToReceiveMidiKey(uint8_t boardIndex, byte midiKey) {
        // We store at {midiKey} location in the array, the corresponding board
        _boardIndexReferences[(uint8_t) midiKey] = boardIndex;

    }

    virtual void handleNoteOn(byte note) {
        // TODO Try to handle things differently so that we can send a midi Message to multiple boards
        // So store vector of bytes
        if (_boardIndexReferences[(uint8_t) note] == INACTIVE_BOARD_INDEX) {
            String message{"WARNING : No linked Board to note "};
            message += note;
            _debugHelper->add(message);
        } else {
            _manager->triggerOnBoard(_boardIndexReferences[(uint8_t) note]);
        }

    }

    virtual void handleNoteOff(byte note) {
//        if (_boardIndexReferences[note] == INACTIVE_PIN) {
//            String message{"WARNING : No linked Board to note "};
//            message += note;
//            _debugHelper->add(message);
//        }

    }

public:
    const uint8_t INACTIVE_BOARD_INDEX{100}; // arbitrary value for a board without MidiKey Connected.
    // We can't use 0, because board 0 exists and can be triggered

protected:
    LedBoardsManager *_manager;
    Debug_Helper *_debugHelper;
    uint8_t _boardIndexReferences[128]{};

};

#endif //PLATFORMIO_PROGRAM_MIDIKEYRECEIVER_H