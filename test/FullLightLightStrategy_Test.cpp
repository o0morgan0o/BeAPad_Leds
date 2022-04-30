//
// Created by morgan on 4/25/2022.
//
#include <gtest/gtest.h>
#include "FakeLedBoard.h"

TEST(FullLightTest, testOfBasicProperties) {
//    auto factory = std::make_unique<LightStrategy_Factory>();
//    auto board = std::make_unique<FakeLedBoard>(factory.get());
//    auto strategy = board->getLightStrategy();
//    //
//    EXPECT_EQ(board->getBoardBaseColor().r, 100);
//    EXPECT_EQ(board->getBoardBaseColor().g, 0);
//    EXPECT_EQ(board->getBoardBaseColor().b, 0);
//    //
//    EXPECT_EQ(strategy->getBirthTime(), 0);
//    EXPECT_EQ(strategy->getStrategyColor().r, 100);
//    EXPECT_EQ(strategy->getStrategyColor().g, 0);
//    EXPECT_EQ(strategy->getStrategyColor().b, 0);
//    board->setBoardColor(100, 101, 102);
//    board->update(200);
//    board->changeLightStrategy(LIGHT_STRATEGIES::STRATEGY_FULL_LIGHT);
//    //
//    auto color = board->getBoardBaseColor();
//    auto newStrategy = board->getLightStrategy();
//    EXPECT_NE(dynamic_cast<FullLightStrategy*>(newStrategy), nullptr);
//    EXPECT_EQ(color.r, 100);
//    EXPECT_EQ(color.g, 101);
//    EXPECT_EQ(color.b, 102);
//
//    EXPECT_EQ(newStrategy->getBirthTime(), 200);
//    EXPECT_EQ(newStrategy->getStrategyColor().r, 100);
//    EXPECT_EQ(newStrategy->getStrategyColor().g, 101);
//    EXPECT_EQ(newStrategy->getStrategyColor().b, 102);



}