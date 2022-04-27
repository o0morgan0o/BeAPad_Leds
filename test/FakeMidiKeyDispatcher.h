//
// Created by morgan on 4/27/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKEMIDIKEYDISPATCHER_H
#define GONZY_PROJECT_TEST_FAKEMIDIKEYDISPATCHER_H
#define  IN_TESTING

#include "../src/MidiKeyDispatcher.h"
#include "../src/LedBoardsManager.h"
#include "../src/Debug_Helper.h"

class FakeMidiKeyDispatcher : public MidiKeyDispatcher {
public:
    FakeMidiKeyDispatcher(LedBoardsManager *manager, Debug_Helper *debugHelper) : MidiKeyDispatcher(manager, debugHelper) {

    }

    uint8_t *getBoardIndexReferences() { return _boardIndexReferences; }

};

#endif //GONZY_PROJECT_TEST_FAKEMIDIKEYDISPATCHER_H