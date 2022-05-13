//
// Created by morgan on 5/12/2022.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FakeLedBoardManager.h"
#include "FakeLedBoardStore.h"
#include "FakeLedBoard.h"
#include "FakeMidiKeyReceiver.h"
#include "Fake_Sensor.h"
#include "Fake_MidiHandler.h"
#include "../src/Debug_Helper.h"
#include "../src/CapacitiveTouch_Dispatcher.h"

class SendMidiKeys_Fixture : public testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    struct Mock_Manager : public FakeLedBoardManager {
    public:
        Mock_Manager(LedBoard_Store_Interface *store, LightStrategy_Factory *factory)
                : FakeLedBoardManager(store, factory) {}

        MOCK_METHOD((void), triggerOnBoard, (uint8_t), (override));
        MOCK_METHOD((void), triggerOffBoard, (uint8_t), (override));

    };

    struct Mock_MidiHandler : public Fake_MidiHandler {
    public:
        Mock_MidiHandler(MidiKeyReceiver *receiver, MidiKeySender *sender, Debug_Helper *debugHelper) :
                Fake_MidiHandler(receiver, sender, debugHelper) {
        }

        void init() override {
        }

        MOCK_METHOD((void), sendMidiOnByTouchPin, (uint8_t, bool), (override));
        MOCK_METHOD((void), sendMidiOffByTouchPin, (uint8_t, bool), (override));

        void loop() override {
            // FAKE
        }
    };
};

TEST_F(SendMidiKeys_Fixture, TestBoardSendCorrectNoteOn) {
    auto store = std::make_unique<FakeLedBoardStore>();
    auto strategyFactory = std::make_unique<LightStrategy_Factory>();
    auto fakeBoard = std::make_unique<FakeLedBoard>(0, 9, strategyFactory.get());
    auto fakeBoard2 = std::make_unique<FakeLedBoard>(1, 9, strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<Mock_Manager>(store.get(), strategyFactory.get());
    auto debugHelper = make_unique<Debug_Helper>();
    //
    auto midiReceiver = make_unique<FakeMidiKeyReceiver>(manager.get(), debugHelper.get());
    auto midiSender = make_unique<MidiKeySender>(manager.get(), debugHelper.get());
    auto midiHandler = make_unique<Mock_MidiHandler>(midiReceiver.get(), midiSender.get(), debugHelper.get());
    midiSender->connectBoardToSendMidiKey(0, 3, 60, 70);
    midiSender->connectBoardToSendMidiKey(1, 4, 61, 71);
    //
    auto fakeSensor = make_unique<Fake_Sensor>();
    auto dispatcher = make_unique<CapacitiveTouch_Dispatcher>(manager.get(), midiHandler.get(), debugHelper.get(), fakeSensor.get());
    //
    EXPECT_EQ(midiSender->getMidiKeyAssociatedWithPinIndex(0), 60);
    EXPECT_EQ(midiSender->getMidiKeyAssociatedWithPinIndex(1), 61);
    EXPECT_EQ(midiSender->getShiftMidiKeyAssociatedWithPinIndex(0), 70);
    EXPECT_EQ(midiSender->getShiftMidiKeyAssociatedWithPinIndex(1), 71);
    //
    fakeSensor->setFakeValue(0b0000000000000000);
    EXPECT_CALL(*midiHandler.get(), sendMidiOnByTouchPin(testing::_, testing::_)).Times(0);
    EXPECT_CALL(*midiHandler.get(), sendMidiOffByTouchPin(testing::_, testing::_)).Times(0);
    dispatcher->loop();
    //
    // now we set a touchValue
    fakeSensor->setFakeValue(0b0000000000000001);
    EXPECT_CALL(*midiHandler.get(), sendMidiOnByTouchPin(0, false)).Times(1);
    EXPECT_CALL(*manager.get(), triggerOnBoard(3));
    dispatcher->loop();
    // reset
    fakeSensor->setFakeValue(0b0000000000000000);
    EXPECT_CALL(*midiHandler.get(), sendMidiOffByTouchPin(0, false)).Times(1);
    EXPECT_CALL(*manager.get(), triggerOffBoard(3));
    dispatcher->loop();

}

TEST_F(SendMidiKeys_Fixture, testSet2PinsAtSameTime){
    auto store = std::make_unique<FakeLedBoardStore>();
    auto strategyFactory = std::make_unique<LightStrategy_Factory>();
    auto fakeBoard = std::make_unique<FakeLedBoard>(0, 9, strategyFactory.get());
    auto fakeBoard2 = std::make_unique<FakeLedBoard>(1, 9, strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<Mock_Manager>(store.get(), strategyFactory.get());
    auto debugHelper = make_unique<Debug_Helper>();
    //
    auto midiReceiver = make_unique<FakeMidiKeyReceiver>(manager.get(), debugHelper.get());
    auto midiSender = make_unique<MidiKeySender>(manager.get(), debugHelper.get());
    auto midiHandler = make_unique<Fake_MidiHandler>(midiReceiver.get(), midiSender.get(), debugHelper.get());
    midiSender->connectBoardToSendMidiKey(0, 3, 60, 70);
    midiSender->connectBoardToSendMidiKey(1, 4, 61, 71);
    //
    auto fakeSensor = make_unique<Fake_Sensor>();
    auto dispatcher = make_unique<CapacitiveTouch_Dispatcher>(manager.get(), midiHandler.get(), debugHelper.get(), fakeSensor.get());
    //
    // now we set 2 touchValues
    fakeSensor->setFakeValue(0b0000000000000011);
    EXPECT_CALL(*manager.get(), triggerOffBoard(3)).Times(0);
    EXPECT_CALL(*manager.get(), triggerOffBoard(4)).Times(0);
    EXPECT_CALL(*manager.get(), triggerOnBoard(3)).Times(1);
    EXPECT_CALL(*manager.get(), triggerOnBoard(4)).Times(1);
    dispatcher->loop();

}