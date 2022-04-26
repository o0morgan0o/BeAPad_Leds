//
// Created by morgan on 4/25/2022.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#define IN_TESTING

#include "FakeLedBoardManager.h"
#include "FakeLedBoardStore.h"
#include "Fake_CRGB.h"
#include "FakeLedBoard.h"

struct LedBoardManager_Fixture : public testing::Test {
    struct LedBoardManager_Mock : public FakeLedBoardManager {
        explicit LedBoardManager_Mock(
                LedBoard_Store_Interface *store,
                LightStrategy_Factory *factory
        ) : FakeLedBoardManager(store, factory) {}

        MOCK_METHOD(void, showGlobally, (CRGB), (override));

    };

protected:
    void SetUp() override {
        Test::SetUp();
    }

    void TearDown() override {
        Test::TearDown();
    }
};

TEST_F(LedBoardManager_Fixture, testShowGloablly) {
    auto factory = std::make_unique<LightStrategy_Factory>();
    auto store = std::make_unique<FakeLedBoardStore>();
    auto manager = std::make_unique<LedBoardManager_Mock>(store.get(), factory.get());
    CRGB color{120, 0, 0};
    EXPECT_CALL(*manager, showGlobally(testing::_)).Times(1);
    manager->showGlobally(CRGB{120, 0, 0});

}