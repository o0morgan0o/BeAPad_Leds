//
// Created by morgan on 4/27/2022.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#define  IN_TESTING

#include "../src/MidiKeyReceiver.h"
#include "FakeLedBoardManager.h"
#include "FakeLedBoardStore.h"
#include "FakeMidiKeyReceiver.h"
#include "FakeLedBoard.h"

struct MidiKeyDispatcher_Fixture : public testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    struct Mock_DebugHelper : public Debug_Helper {
        Mock_DebugHelper() : Debug_Helper() {}

        MOCK_METHOD(void, add, (const String&), (override));
    };

    struct Mock_FakeLedBoardsManager : public FakeLedBoardManager {
        Mock_FakeLedBoardsManager(LedBoard_Store_Interface *store, LightStrategy_Factory *factory)
                : FakeLedBoardManager(store, factory) {}

        MOCK_METHOD(void, triggerOnBoard, (uint8_t), (override));

    };
};

TEST(MidiKeyDispatcherTest, checkInitializationOfInternalArrayOfDispatcher) {
    auto store = make_unique<FakeLedBoardStore>();
    auto strategyFactory = make_unique<LightStrategy_Factory>();
    auto fakeBoard = make_unique<FakeLedBoard>(0, 9 ,strategyFactory.get());
    auto fakeBoard2 = make_unique<FakeLedBoard>(0, 9 ,strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<FakeLedBoardManager>(store.get(), strategyFactory.get());
    auto debugHelper = make_unique<Debug_Helper>();
    //
    auto dispatcher = make_unique<FakeMidiKeyReceiver>(manager.get(), debugHelper.get());
    //
    EXPECT_EQ(dispatcher->INACTIVE_BOARD_INDEX, 100);
    auto boardIndexReferences = dispatcher->getBoardIndexReferences();
    EXPECT_EQ(boardIndexReferences[0], dispatcher->INACTIVE_BOARD_INDEX);
    EXPECT_EQ(boardIndexReferences[1], dispatcher->INACTIVE_BOARD_INDEX);
    EXPECT_EQ(boardIndexReferences[127], dispatcher->INACTIVE_BOARD_INDEX);
    //
    dispatcher->connectBoardToReceiveMidiKey(1, byte{80});
    EXPECT_EQ(boardIndexReferences[80], 1);
    EXPECT_EQ(boardIndexReferences[1], dispatcher->INACTIVE_BOARD_INDEX); // test just a random other midiKey, should not be set
    dispatcher->connectBoardToReceiveMidiKey(0, byte{90});
    EXPECT_EQ(boardIndexReferences[80], 1);
    EXPECT_EQ(boardIndexReferences[90], 0);

}

TEST_F(MidiKeyDispatcher_Fixture, testThatNonConnectedBoardSendMessageToDebugHelper) {
    auto store = make_unique<FakeLedBoardStore>();
    auto strategyFactory = make_unique<LightStrategy_Factory>();
    auto fakeBoard = make_unique<FakeLedBoard>(0,9, strategyFactory.get());
    auto fakeBoard2 = make_unique<FakeLedBoard>(0,9, strategyFactory.get());
    store->addBoard(fakeBoard.get());
    store->addBoard(fakeBoard2.get());
    auto manager = std::make_unique<Mock_FakeLedBoardsManager>(store.get(), strategyFactory.get());
    auto debugHelper = make_unique<Mock_DebugHelper>();
    //
    auto dispatcher = make_unique<FakeMidiKeyReceiver>(manager.get(), debugHelper.get());
    dispatcher->connectBoardToReceiveMidiKey(0, byte{82});
    dispatcher->connectBoardToReceiveMidiKey(1, byte{84});
    //
    EXPECT_CALL(*debugHelper.get(), add(testing::_)).Times(1);
    dispatcher->handleNoteOn(byte{34});
    EXPECT_CALL(*manager.get(), triggerOnBoard(0)).Times(1);
    dispatcher->handleNoteOn(byte{82});
    EXPECT_CALL(*manager.get(), triggerOnBoard(1)).Times(2);
    dispatcher->handleNoteOn(byte{84});
    dispatcher->handleNoteOn(byte{84});

}