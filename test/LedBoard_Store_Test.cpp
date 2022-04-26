//
// Created by morgan on 4/25/2022.
//
#include <gtest/gtest.h>

#define IN_TESTING
#include "FakeLedBoardStore.h"
#include "FakeLedBoard.h"


struct LedBoardStore_Fixture : public testing::Test {
    struct LedBoardStore_Mock : public FakeLedBoardStore {


    };

public:
    std::unique_ptr<LightStrategy_Factory> factory;

    void SetUp() override {
        factory = std::make_unique<LightStrategy_Factory>();
    }

    void TearDown() override {
    }

};

TEST_F(LedBoardStore_Fixture, checkEmptyStateOfLedBoardStore) {
    FakeLedBoardStore ledBoardStore{};
    EXPECT_EQ(ledBoardStore.getLedBoards().size(), 0);
}

TEST_F(LedBoardStore_Fixture, checkAddOfBoards){
    FakeLedBoardStore ledBoardStore{};
    for (uint8_t i = 0; i < 8; i++){
        ledBoardStore.addBoard(new FakeLedBoard(factory.get()));
    }
    EXPECT_EQ(ledBoardStore.getLedBoards().size(), 8);
}

TEST_F(LedBoardStore_Fixture, checkBoardShouldHaveAFactoryAndALightStrategy) {
    FakeLedBoardStore ledBoardStore{};
    ledBoardStore.addBoard(new FakeLedBoard(factory.get()));
    EXPECT_EQ(ledBoardStore.getLedBoards().size(), 1);
    auto board = ledBoardStore.getLedBoards().at(0);
    EXPECT_NE(board, nullptr);
    auto fakeBoard = dynamic_cast<FakeLedBoard*>(board);
    auto boardStrategyFactory = fakeBoard->getLightStrategyFactory();
    //
    EXPECT_EQ(factory.get(), boardStrategyFactory); // address of factory should be the same
    //
    auto boardStrategy = fakeBoard->getLightStrategy();
    EXPECT_NE(boardStrategy,nullptr);
    EXPECT_NE(dynamic_cast<NoLightStrategy*>(boardStrategy), nullptr);
}