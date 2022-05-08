//
// Created by morgan on 5/1/2022.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "FakeLedBoardManager.h"
#include "FakeLedBoardStore.h"
#include "FakeLedBoard.h"
#include "FakeMidiKeyReceiver.h"
#include "Fake_MidiHandler.h"
#include "../src/Debug_Helper.h"
#include "../src/CapacitiveTouch_Dispatcher.h"

struct CapacitiveTest_Fixture : public testing::Test {
    struct Mock_MidiHandler : public Fake_MidiHandler {
    public:
        Mock_MidiHandler(MidiKeyReceiver *receiver, MidiKeySender *sender, Debug_Helper *debugHelper) :
                Fake_MidiHandler(receiver, sender, debugHelper) {

        }

        void init() override {
        }

        MOCK_METHOD((void), sendMidiNoteOn, (uint8_t), (override));


//        void sendMidiNoteOn(uint8_t pinIndex) override {
//            // MOCK
//        }

        void loop() override {
            // FAKE
        }
    };

    struct CapacitiveTouch_Dispatcher_Mock : public CapacitiveTouch_Dispatcher {
        CapacitiveTouch_Dispatcher_Mock(LedBoardsManager *manager, Midi_Handler *midiHandler, Debug_Helper *debugHelper)
                : CapacitiveTouch_Dispatcher(manager, midiHandler, debugHelper) {

        }

        void begin() override {

        }

        void loop() override {

        }

        void connectBoardToCapacitiveSensor(uint8_t boardIndex, uint8_t capacitiveSensorIndex) override {

        }

        void setTouchThreshold(uint8_t newThreshold) override {

        }

        void setReleaseThreashold(uint8_t newThreshold) override {

        }

        uint8_t getTouchThreshold() const override {
            return 0;
        }

        uint8_t getReleaseThreashold() const override {
            return 0;
        }

    };

protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(CapacitiveTest_Fixture, testConnectionPinToBoard) {
    auto store = std::make_unique<FakeLedBoardStore>();
    auto strategyFactory = std::make_unique<LightStrategy_Factory>();
    auto fakeBoard = std::make_unique<FakeLedBoard>(0, 9, strategyFactory.get());
    auto fakeBoard2 = std::make_unique<FakeLedBoard>(1, 9, strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<FakeLedBoardManager>(store.get(), strategyFactory.get());
    auto debugHelper = make_unique<Debug_Helper>();
    //
    auto midiReceiver = make_unique<FakeMidiKeyReceiver>(manager.get(), debugHelper.get());
    auto midiSender = make_unique<MidiKeySender>(manager.get(), debugHelper.get());
    midiSender->connectBoardToSendMidiKey(1, 0, 60);
    midiSender->connectBoardToSendMidiKey(2, 1, 61);
    //
    EXPECT_EQ(midiSender->getBoardAssociatedWithPinIndex(1), 0);
    EXPECT_EQ(midiSender->getBoardAssociatedWithPinIndex(2), 1);
    //
    auto fakeMidiHandler = std::make_unique<Fake_MidiHandler>(midiReceiver.get(), midiSender.get(), debugHelper.get());
    EXPECT_EQ(fakeMidiHandler->getBoardAssociatedWithTouchPin(1), 0); // PIN 1 should be associated with board 0
    EXPECT_EQ(fakeMidiHandler->getBoardAssociatedWithTouchPin(2), 1); // PIN 1 should be associated with board 0


}

TEST_F(CapacitiveTest_Fixture, testMidihandlerSendMidiFromPinToCorrectNote){
    auto store = std::make_unique<FakeLedBoardStore>();
    auto strategyFactory = std::make_unique<LightStrategy_Factory>();
    auto fakeBoard = std::make_unique<FakeLedBoard>(0, 9, strategyFactory.get());
    auto fakeBoard2 = std::make_unique<FakeLedBoard>(1, 9, strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<FakeLedBoardManager>(store.get(), strategyFactory.get());
    auto debugHelper = make_unique<Debug_Helper>();
    //
    auto midiReceiver = make_unique<FakeMidiKeyReceiver>(manager.get(), debugHelper.get());
    auto midiSender = make_unique<MidiKeySender>(manager.get(), debugHelper.get());
    midiSender->connectBoardToSendMidiKey(1, 0, 60);
    midiSender->connectBoardToSendMidiKey(2, 1, 61);
    //
    EXPECT_EQ(midiSender->getMidiKeyAssociatedWithPinIndex(1), 60);
    EXPECT_EQ(midiSender->getMidiKeyAssociatedWithPinIndex(2), 61);

}