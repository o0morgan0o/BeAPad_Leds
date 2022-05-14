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
        for (unsigned char &boardIndexReference: _boardIndexReferences) {
            boardIndexReference = INACTIVE_BOARD_INDEX;
        }

        // initialization of emptyStrategies
        for (auto &midiNotesStrategy: _midiNotesStrategies) {
            midiNotesStrategy = LIGHT_STRATEGIES::NO_LIGHT_STRATEGY;
        }
    }

//    virtual void connectBoardToReceiveMidiKey(uint8_t boardIndex, byte midiKey) {
//        // We store at {midiKey} location in the array, the corresponding board
//        _boardIndexReferences[(uint8_t) midiKey] = boardIndex;
//    }

    virtual void connectBoardToReceiveMidiKey(uint8_t boardIndex, byte midiKey, LIGHT_STRATEGIES strategy) {
        // We store at {midiKey} location in the array, the corresponding board
        _boardIndexReferences[(uint8_t) midiKey] = boardIndex;
        _midiNotesStrategies[(uint8_t) midiKey] = strategy;

    }

    virtual void handleNoteOn(byte channel, byte note) {
        // TODO Try to handle things differently so that we can send a midi Message to multiple boards
        // So store vector of bytes
        auto strategy = _manager->getLightStrategyAssociatedWithChannel(channel);
        _manager->triggerOnBoard(_boardIndexReferences[(uint8_t) note], strategy);
//        if (_boardIndexReferences[(uint8_t) note] == INACTIVE_BOARD_INDEX) {
//            _debugHelper->add("WARNING : No linked Board to note");
//        } else {
//        }

    }

    virtual void handleNoteOff(byte note) {
//        if (_boardIndexReferences[note] == UNDEFINED_NOTE) {
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
    LIGHT_STRATEGIES _midiNotesStrategies[128]{};

};

#endif //PLATFORMIO_PROGRAM_MIDIKEYRECEIVER_H