#include <gtest/gtest.h>
#define  IN_TESTING
#include <vector>
#include <memory>
#include "../src/LightStrategy_Factory.h"
#include "FakeLedBoard.h"
#include "FakeLedBoardManager.h"
#include "FakeLedBoardStore.h"

TEST(myTest, testFirst){
    EXPECT_EQ(1,1);
    auto factory = std::make_unique<LightStrategy_Factory>();
    FakeLedBoard fakeBoard{9, factory.get()};
}

TEST(BoardCreation, testManagerGetAllCreatedBoards){
    auto factory = std::make_unique<LightStrategy_Factory>();
    auto store = std::make_unique<FakeLedBoardStore>();
    store->addBoard(new FakeLedBoard(9, factory.get()));
    store->addBoard(new FakeLedBoard(9, factory.get()));
    store->addBoard(new FakeLedBoard(9, factory.get()));
    store->addBoard(new FakeLedBoard(9, factory.get()));
    store->addBoard(new FakeLedBoard(9, factory.get()));
    store->addBoard(new FakeLedBoard(9, factory.get()));
    store->addBoard(new FakeLedBoard(9, factory.get()));
    store->addBoard(new FakeLedBoard(9, factory.get()));
    EXPECT_EQ(store->getLedBoards().size(), 8);
}