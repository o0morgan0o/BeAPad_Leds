//
// Created by morgan on 4/25/2022.
//

#include <gtest/gtest.h>
#define IN_TESTING
#include "FakeLedBoard.h"

struct LedBoard_Fixture :public testing::Test{

    struct LedBoard_Mock : public FakeLedBoard{
        void show() override {

        }


    };
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(LedBoard_Fixture, testInitialCreation){
    FakeLedBoard ledBoard;
//    EXPECT_EQ(ledBoard.getCurrentTime(), 0.0);
}

TEST_F(LedBoard_Fixture, testUpdateTime) {
    LedBoard_Mock ledBoard;
    ledBoard.update(120.0);
    EXPECT_EQ(ledBoard.getCurrentTime(), 120.0);
}