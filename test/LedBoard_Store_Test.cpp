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

protected:
    void SetUp() override {
        Test::SetUp();
    }

    void TearDown() override {
        Test::TearDown();
    }

};

TEST_F(LedBoardStore_Fixture, checkEmptyStateOfLedBoardStore) {
    FakeLedBoardStore ledBoardStore{};
    EXPECT_EQ(ledBoardStore.getLedBoards().size(), 0);
}

TEST_F(LedBoardStore_Fixture, checkAddOfBoards){
    FakeLedBoardStore ledBoardStore{};
    for (uint8_t i = 0; i < 8; i++){
        ledBoardStore.addBoard(new FakeLedBoard());
    }
    EXPECT_EQ(ledBoardStore.getLedBoards().size(), 8);


}