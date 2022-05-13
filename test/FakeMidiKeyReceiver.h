//
// Created by morgan on 4/27/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKEMIDIKEYRECEIVER_H
#define GONZY_PROJECT_TEST_FAKEMIDIKEYRECEIVER_H
#define  IN_TESTING

#include "../src/MidiKeyReceiver.h"
#include "../src/LedBoardsManager.h"
#include "../src/Debug_Helper.h"

class FakeMidiKeyReceiver : public MidiKeyReceiver {
public:
    FakeMidiKeyReceiver(LedBoardsManager *manager, Debug_Helper *debugHelper) : MidiKeyReceiver(manager, debugHelper) {

    }

    uint8_t *getBoardIndexReferences() {
        return _boardIndexReferences;
    }

    LIGHT_STRATEGIES* getLightStrategiesArray(){
        return _midiNotesStrategies;
    }

};

#endif //GONZY_PROJECT_TEST_FAKEMIDIKEYRECEIVER_H