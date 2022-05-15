//
// Created by morgan on 5/15/2022.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FakeLedBoardManager.h"
#include "FakeLedBoardStore.h"
#include "FakeLedBoard.h"
#include "FakeMidiKeyReceiver.h"
#include "Fake_Sensor.h"
#include "Fake_MidiHandler.h"

struct SerpentinFixture : public testing::Test {
    struct Fake_SerpentinLightStrategy : public SerpentinLightStrategy {
        explicit Fake_SerpentinLightStrategy(LedBoard *ledBoard) : SerpentinLightStrategy(ledBoard) {}

        SerpentinSingleLed *getSerpentinLeds() {
            return _serpentinLeds;
        }

    };

protected:
    std::unique_ptr<FakeLedBoard> ledBoard;
    std::unique_ptr<LightStrategy_Factory> factory;
    std::unique_ptr<Fake_SerpentinLightStrategy> serpentinStrategy;

    void SetUp() override {
        factory = std::make_unique<LightStrategy_Factory>();
        ledBoard = std::make_unique<FakeLedBoard>(9, factory.get());
        serpentinStrategy = std::make_unique<Fake_SerpentinLightStrategy>(ledBoard.get());
    }

    void TearDown() override {
        Test::TearDown();
    }

};

TEST_F(SerpentinFixture, testCorrectInitializationOfSerpentinsInBoard) {
    auto serpentinLeds = serpentinStrategy->getSerpentinLeds();
    for (uint8_t i = 0; i < 9; i++) {
        EXPECT_EQ(serpentinLeds[i].getLifeExpectancy(), 0);
    }
    EXPECT_EQ(serpentinLeds[0].getDelayBeforeStart(), 0);
    EXPECT_EQ(serpentinLeds[1].getDelayBeforeStart(), 200);
    EXPECT_EQ(serpentinLeds[2].getDelayBeforeStart(), 400);
    EXPECT_EQ(serpentinLeds[3].getDelayBeforeStart(), 600);
}

TEST_F(SerpentinFixture, testTriggerOnSetCorrectStartTime){
    serpentinStrategy->updateValues(456);
    auto serpentinLeds = serpentinStrategy->getSerpentinLeds();
    EXPECT_EQ(serpentinLeds[0].getStartTime(), 0);
    EXPECT_EQ(serpentinLeds[0].getLifeExpectancy(), 0);
    serpentinStrategy->triggerOn();
    EXPECT_EQ(serpentinLeds[0].getStartTime(), 456 );
    EXPECT_EQ(serpentinLeds[0].getLifeExpectancy(), 1000);
    EXPECT_EQ(serpentinLeds[1].getStartTime(), 656);
    EXPECT_EQ(serpentinLeds[2].getStartTime(), 856);

}

TEST_F(SerpentinFixture, testThatWeGetTheCorrectColor){
    auto serpentinLeds = serpentinStrategy->getSerpentinLeds();
//    serpentinStrategy->updateValues(456);
    serpentinStrategy->triggerOn();
    //
    // index 0
    EXPECT_EQ(serpentinLeds[0].getIsInLifeSpan(34), true);
    EXPECT_EQ(serpentinLeds[0].getIsInLifeSpan(1002), false);
    // index 1
    EXPECT_EQ(serpentinLeds[1].getIsInLifeSpan(34), false);
    EXPECT_EQ(serpentinLeds[1].getIsInLifeSpan(180), false);
    EXPECT_EQ(serpentinLeds[1].getIsInLifeSpan(202), true);
    EXPECT_EQ(serpentinLeds[1].getIsInLifeSpan(1190), true);
    EXPECT_EQ(serpentinLeds[1].getIsInLifeSpan(1204), false);
    // index 2
    EXPECT_EQ(serpentinLeds[2].getIsInLifeSpan(389), false);
    EXPECT_EQ(serpentinLeds[2].getIsInLifeSpan(403), true);
    EXPECT_EQ(serpentinLeds[2].getIsInLifeSpan(1398), true);
    EXPECT_EQ(serpentinLeds[2].getIsInLifeSpan(1402), false);
}