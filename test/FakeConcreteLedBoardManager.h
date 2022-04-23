//
// Created by morgan on 4/23/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKECONCRETELEDBOARDMANAGER_H
#define GONZY_PROJECT_TEST_FAKECONCRETELEDBOARDMANAGER_H

#define IN_TESTING
#include "Fake_CRGB.h"
#include "../src/ConcreteLedBoardsManager.h"

class FakeConcreteLedBoardManager : public ConcreteLedBoardsManager{
public:

     FakeConcreteLedBoardManager(const std::vector<ILedBoard *> &ledBoards): ConcreteLedBoardsManager(ledBoards){}

//    void init() override;
//
//    void lightAll() override;
//
//    void show() override;
//
//    void update(unsigned long currentTime) override;
//
//    void setRandomColorForEachBoard() override;
//    // added functions
//
//    std::vector<ILedBoard*> getLedBoardsVector(){ return _ledBoards;}


};

#endif //GONZY_PROJECT_TEST_FAKECONCRETELEDBOARDMANAGER_H