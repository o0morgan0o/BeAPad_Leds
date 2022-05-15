//
// Created by morgan on 4/25/2022.
//

#include <gtest/gtest.h>
#define IN_TESTING
#include "../src/LightStrategy.h"
#include "../src/LightStrategy_Factory.h"
#include "FakeLedBoard.h"

TEST(LightStrategyFactory, basicCreationTest){
    auto factory = std::make_unique<LightStrategy_Factory>();
    auto fakeBoard = std::make_unique<FakeLedBoard>( 9,factory.get());
    auto noLightStrategy = factory->makeNoLightStrategy(fakeBoard.get());
    EXPECT_NE(dynamic_cast<NoLightStrategy*>(noLightStrategy), nullptr);
    noLightStrategy->updateValues(0);
}