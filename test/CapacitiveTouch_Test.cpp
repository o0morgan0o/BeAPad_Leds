//
// Created by morgan on 5/1/2022.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "FakeLedBoardManager.h"
#include "FakeLedBoardStore.h"
#include "FakeLedBoard.h"
#include "FakeMidiKeyDispatcher.h"
#include "Fake_MidiHandler.h"
#include "../src/Debug_Helper.h"
#include "../src/CapacitiveTouch_Dispatcher.h"

struct CapacitiveTest_Fixture : public testing::Test {

    struct Mock_MidiHandler : public Fake_MidiHandler{
    public:
        Mock_MidiHandler(MidiKeyDispatcher *dispatcher, Debug_Helper *debugHelper):
        Fake_MidiHandler(dispatcher,debugHelper){

        }
        void init() override {
        }

        void sendMidiNoteOn() override {
            // MOCK
        }

        void loop() override {
            // FAKE
        }
    };
    struct CapacitiveTouch_Dispatcher_Mock : public CapacitiveTouch_Dispatcher {
        CapacitiveTouch_Dispatcher_Mock(Midi_Handler *midiHandler, Debug_Helper *debugHelper)
                : CapacitiveTouch_Dispatcher(midiHandler, debugHelper) {

        }

        uint16_t getTouchReadValueOnPin(uint8_t pin) override {
            // MOCK
            return 0;
        }

    };

protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(CapacitiveTest_Fixture, testBasicRead) {
    auto store = std::make_unique<FakeLedBoardStore>();
    auto strategyFactory = std::make_unique<LightStrategy_Factory>();
    auto fakeBoard = std::make_unique<FakeLedBoard>(strategyFactory.get());
    auto fakeBoard2 = std::make_unique<FakeLedBoard>(strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<FakeLedBoardManager>(store.get(), strategyFactory.get());
    auto debugHelper = make_unique<Debug_Helper>();
    auto dispatcher = make_unique<FakeMidiKeyDispatcher>(manager.get(), debugHelper.get());

    auto fakeMidiHandler = std::make_unique<Fake_MidiHandler>(dispatcher.get(), debugHelper.get());
    auto capacitiveTouch = make_unique<CapacitiveTouch_Dispatcher_Mock>(fakeMidiHandler.get(), debugHelper.get());
    //
    capacitiveTouch->setTouchThreshold(83);
    capacitiveTouch->setReleaseThreashold(23);
    EXPECT_EQ(capacitiveTouch->getTouchThreshold(), 83);
    EXPECT_EQ(capacitiveTouch->getReleaseThreashold(), 23);


}