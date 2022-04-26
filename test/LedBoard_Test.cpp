//
// Created by morgan on 4/25/2022.
//

#include <gtest/gtest.h>
#define IN_TESTING
#include "FakeLedBoard.h"
#include "FakeLedBoardStore.h"
#include "FakeLedBoardManager.h"
#include "../src/LightStrategy_Factory.h"

struct LedBoard_Fixture :public testing::Test{

    struct LedBoard_Mock : public FakeLedBoard{
        explicit LedBoard_Mock(LightStrategy_Factory* factory): FakeLedBoard(factory){}
        void show() override {

        }


    };
public:
    std::unique_ptr<LightStrategy_Factory> factory;
    void SetUp() override {
        factory = std::make_unique<LightStrategy_Factory>();

    }

    void TearDown() override {

    }

};

TEST_F(LedBoard_Fixture, testInitialCreation){
    FakeLedBoard ledBoard{factory.get()};
//    EXPECT_EQ(ledBoard.getCurrentTime(), 0.0);
}

TEST_F(LedBoard_Fixture, testUpdateTime) {
    LedBoard_Mock ledBoard{factory.get()};
    ledBoard.update(120.0);
    EXPECT_EQ(ledBoard.getCurrentTime(), 120.0);
}

TEST_F(LedBoard_Fixture, ledBoardShouldHaveTheLightStrategyFactory){
    auto lightStrategyFactory = std::make_unique<LightStrategy_Factory>();
    auto store = std::make_unique<FakeLedBoardStore>();
    auto manager = std::make_unique<FakeLedBoardManager>( store.get(), lightStrategyFactory.get());

}

TEST_F(LedBoard_Fixture, checkChangingStrategyInBoard) {
    auto fakeBoard = std::make_unique<FakeLedBoard>(factory.get());
    auto boardStrategy = fakeBoard->getLightStrategy();
    EXPECT_NE(dynamic_cast<NoLightStrategy *>(boardStrategy), nullptr);
    fakeBoard->changeLightStrategy(LIGHT_STRATEGIES::STRATEGY_FULL_LIGHT);
    boardStrategy = fakeBoard->getLightStrategy();
    //
    EXPECT_EQ(dynamic_cast<NoLightStrategy * >(boardStrategy), nullptr); // it should not be a noLightStrategy
    EXPECT_NE(dynamic_cast<FullLightStrategy * > (boardStrategy), nullptr); // it should be a fullLightStrategy

}