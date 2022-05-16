//
// Created by morgan on 4/27/2022.
//

#ifndef PLATFORMIO_PROGRAM_MIDIKEYRECEIVER_H
#define PLATFORMIO_PROGRAM_MIDIKEYRECEIVER_H

#include "LedBoardsManager.h"
#include "Debug_Helper.h"

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
    }

    virtual void connectBoardToReceiveMidiKey(uint8_t boardIndex, byte midiKey) {
        // We store at {midiKey} location in the array, the corresponding board
        _boardIndexReferences[(uint8_t) midiKey] = boardIndex;
    }

    virtual void handleNoteOn(byte channel, byte note) {
        auto channelStrategy = _manager->getLightStrategyAssociatedWithChannel(channel);
        auto channelColor = _manager->getColorAssociatedWithChannel(channel);
        _manager->triggerOnBoard(_boardIndexReferences[(uint8_t) note], channelStrategy, channelColor);
    }

    virtual void handleNoteOff(byte note) {
        _manager->triggerOffBoard(_boardIndexReferences[(uint8_t) note]);
    }

    virtual void handleOnSpecialEffect(byte channel, byte note, byte velocity) {
        _manager->triggerOnSpecialEffect(channel, note, velocity);
    }

    virtual void handleOffSpecialEffect(byte channel, byte note, byte velocity) {
        _manager->triggerOffSpecialEffect(channel, note, velocity);
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