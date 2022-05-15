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
    struct Mock_LedBoardManager : public FakeLedBoardManager {
        Mock_LedBoardManager(LedBoard_Store_Interface *store, LightStrategy_Factory *factory, SpecialEffect_Factory *specialEffectFactory, Debug_Helper *debugHelper)
                : FakeLedBoardManager(store, factory, specialEffectFactory, debugHelper) {}

        MOCK_METHOD((void), triggerOnBoard, (uint8_t, LIGHT_STRATEGIES), (override));
        MOCK_METHOD((void), triggerOffBoard, (uint8_t), (override));

    };

    std::unique_ptr<SpecialEffect_Factory> _specialEffectsFactory;
    std::unique_ptr<Debug_Helper> _debugHelper;

    void SetUp() override {
         _specialEffectsFactory = std::make_unique<SpecialEffect_Factory>();
         _debugHelper = std::make_unique<Debug_Helper>();
    }

    void TearDown() override {
    }

};

TEST_F(MidiReceiver_Fixture, testInitializationOfStrategies) {
    auto store = std::make_unique<FakeLedBoardStore>();
    auto strategyFactory = std::make_unique<LightStrategy_Factory>();
    auto fakeBoard = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
    auto fakeBoard2 = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<FakeLedBoardManager>(store.get(), strategyFactory.get(), _specialEffectsFactory.get(), _debugHelper.get());
    //
    auto midiReceiver = std::make_unique<FakeMidiKeyReceiver>(manager.get(), _debugHelper.get());
    //
//    auto allLightStrategies = midiReceiver->getLightStrategiesArray();
//    // check that lightStrategies are no_light_strategies
//    EXPECT_EQ((int) allLightStrategies[0], (int) LIGHT_STRATEGIES::NO_LIGHT_STRATEGY);
//    EXPECT_EQ((int) allLightStrategies[80], (int) LIGHT_STRATEGIES::NO_LIGHT_STRATEGY);
//    EXPECT_EQ((int) allLightStrategies[255], (int) LIGHT_STRATEGIES::NO_LIGHT_STRATEGY);
}

TEST_F(MidiReceiver_Fixture, testSetOfStrategy) {
    auto store = std::make_unique<FakeLedBoardStore>();
    auto strategyFactory = std::make_unique<LightStrategy_Factory>();
    auto fakeBoard = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
    auto fakeBoard2 = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<FakeLedBoardManager>(store.get(), strategyFactory.get(), _specialEffectsFactory.get(), _debugHelper.get());
    auto debugHelper = std::make_unique<Debug_Helper>();
    //
    auto midiReceiver = std::make_unique<FakeMidiKeyReceiver>(manager.get(), debugHelper.get());
//    midiReceiver->connectBoardToReceiveMidiKey(0, (byte) 81, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(0, (byte) 82, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(1, (byte) 83, LIGHT_STRATEGIES::STRATEGY_FULL_LIGHT);
//    midiReceiver->connectBoardToReceiveMidiKey(2, (byte) 84, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    //
//    auto allLightStrategies = midiReceiver->getLightStrategiesArray();
//    // check that lightStrategies are no_light_strategies
//    EXPECT_EQ((int) allLightStrategies[81], (int) LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    EXPECT_EQ((int) allLightStrategies[82], (int) LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
//    EXPECT_EQ((int) allLightStrategies[83], (int) LIGHT_STRATEGIES::STRATEGY_FULL_LIGHT);
//    EXPECT_EQ((int) allLightStrategies[84], (int) LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
}

TEST_F(MidiReceiver_Fixture, testMidiReceiveCallTriggerNoteOnWithCorrectStrategy) {
//    auto store = std::make_unique<FakeLedBoardStore>();
//    auto strategyFactory = std::make_unique<LightStrategy_Factory>();
//    auto fakeBoard = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
//    auto fakeBoard2 = std::make_unique<FakeLedBoard>(9, strategyFactory.get());
//    store->addBoard(fakeBoard.get());
//    store->addBoard(fakeBoard2.get());
//    auto manager = std::make_unique<Mock_LedBoardManager>(store.get(), strategyFactory.get(), _specialEffectsFactory.get(), _debugHelper.get());
//    //
//    auto midiSender = std::make_unique<MidiKeySender>(manager.get(), _debugHelper.get());
//    //
//    auto midiReceiver = std::make_unique<FakeMidiKeyReceiver>(manager.get(), _debugHelper.get());
//    midiReceiver->connectBoardToReceiveMidiKey(4, (byte) 81);
//    //
//    auto midiHandler = std::make_unique<Fake_MidiHandler>(midiReceiver.get(), midiSender.get(), _debugHelper.get());
//    EXPECT_CALL(*manager.get(), triggerOnBoard(4, LIGHT_STRATEGIES::STRATEGY_FADE_OUT));
//    midiReceiver->handleNoteOn((byte) 1 , (byte) 81);
}