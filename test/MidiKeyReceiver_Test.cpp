//
// Created by morgan on 5/13/2022.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "FakeLedBoard.h"
#include "FakeLedBoardStore.h"
#include "FakeLedBoardManager.h"
#include "FakeMidiKeyReceiver.h"
#include "Fake_MidiHandler.h"

struct MidiReceiver_Fixture : public testing::Test {
    struct Mock_LedBoardManager : public FakeLedBoardManager{
        Mock_LedBoardManager(LedBoard_Store_Interface*store, LightStrategy_Factory *factory) : FakeLedBoardManager(store, factory) {}

        MOCK_METHOD((void), triggerOnBoard, (uint8_t, LIGHT_STRATEGIES), (override));
        MOCK_METHOD((void), triggerOffBoard, (uint8_t), (override));

    };
    void TearDown() override {
    }

    void TestBody() override {

    }
};

TEST_F(MidiReceiver_Fixture, testInitializationOfStrategies) {
    auto store = std::make_unique<FakeLedBoardStore>();
    auto strategyFactory = std::make_unique<LightStrategy_Factory>();
    auto fakeBoard = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
    auto fakeBoard2 = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<FakeLedBoardManager>(store.get(), strategyFactory.get());
    auto debugHelper = std::make_unique<Debug_Helper>();
    //
    auto midiReceiver = std::make_unique<FakeMidiKeyReceiver>(manager.get(), debugHelper.get());
    //
    auto allLightStrategies = midiReceiver->getLightStrategiesArray();
    // check that lightStrategies are no_light_strategies
    EXPECT_EQ((int) allLightStrategies[0], (int) LIGHT_STRATEGIES::NO_LIGHT_STRATEGY);
    EXPECT_EQ((int) allLightStrategies[80], (int) LIGHT_STRATEGIES::NO_LIGHT_STRATEGY);
    EXPECT_EQ((int) allLightStrategies[255], (int) LIGHT_STRATEGIES::NO_LIGHT_STRATEGY);
}

TEST_F(MidiReceiver_Fixture, testSetOfStrategy) {
    auto store = std::make_unique<FakeLedBoardStore>();
    auto strategyFactory = std::make_unique<LightStrategy_Factory>();
    auto fakeBoard = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
    auto fakeBoard2 = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<FakeLedBoardManager>(store.get(), strategyFactory.get());
    auto debugHelper = std::make_unique<Debug_Helper>();
    //
    auto midiReceiver = std::make_unique<FakeMidiKeyReceiver>(manager.get(), debugHelper.get());
    midiReceiver->connectBoardToReceiveMidiKey(0, (byte) 81, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    midiReceiver->connectBoardToReceiveMidiKey(0, (byte) 82, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
    midiReceiver->connectBoardToReceiveMidiKey(1, (byte) 83, LIGHT_STRATEGIES::STRATEGY_FULL_LIGHT);
    midiReceiver->connectBoardToReceiveMidiKey(2, (byte) 84, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    //
    auto allLightStrategies = midiReceiver->getLightStrategiesArray();
    // check that lightStrategies are no_light_strategies
    EXPECT_EQ((int) allLightStrategies[81], (int) LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    EXPECT_EQ((int) allLightStrategies[82], (int) LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
    EXPECT_EQ((int) allLightStrategies[83], (int) LIGHT_STRATEGIES::STRATEGY_FULL_LIGHT);
    EXPECT_EQ((int) allLightStrategies[84], (int) LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
}

TEST_F(MidiReceiver_Fixture, testMidiReceiveCallTriggerNoteOnWithCorrectStrategy) {
    auto store = std::make_unique<FakeLedBoardStore>();
    auto strategyFactory = std::make_unique<LightStrategy_Factory>();
    auto fakeBoard = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
    auto fakeBoard2 = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<Mock_LedBoardManager>(store.get(), strategyFactory.get());
    auto debugHelper = std::make_unique<Debug_Helper>();
    //
    auto midiSender = make_unique<MidiKeySender>(manager.get(), debugHelper.get());
    //
    auto midiReceiver = std::make_unique<FakeMidiKeyReceiver>(manager.get(), debugHelper.get());
    midiReceiver->connectBoardToReceiveMidiKey(4, (byte) 81, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    //
    auto midiHandler = make_unique<Fake_MidiHandler>(midiReceiver.get(), midiSender.get(), debugHelper.get());
    EXPECT_CALL(*manager.get(), triggerOnBoard(4, LIGHT_STRATEGIES::STRATEGY_FADE_OUT));
    midiReceiver->handleNoteOn((byte) 81);
}