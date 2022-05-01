//
// Created by morgan on 5/1/2022.
//
#include <gtest/gtest.h>
#include "../src/PinStateValidator.h"
#include <memory>

struct PinStateValidator_Fixture : public testing::Test {
public:
    uint8_t TOUCH_THRESHOLD = 25;
    uint8_t RELEASE_THRESHOLD = 40;
    std::unique_ptr<PinStateValidator> validator;

    void SetUp() override {
        validator = std::make_unique<PinStateValidator>();
        validator->init(&TOUCH_THRESHOLD, &RELEASE_THRESHOLD);
    }

    void TearDown() override {
    }
};

TEST_F(PinStateValidator_Fixture, testImmutability) {
    EXPECT_EQ(validator->getCurrIsTouched(), false);
    EXPECT_EQ(validator->getPrevIsTouched(), false);
    EXPECT_EQ(validator->getPrevPrevIsTouched(), false);
    //
    EXPECT_EQ(validator->getCurrIsReleased(), false);
    EXPECT_EQ(validator->getPrevIsReleased(), false);
    EXPECT_EQ(validator->getPrevPrevIsReleased(), false);
    //
    EXPECT_EQ(validator->getStateIsTouched(), false);
}

TEST_F(PinStateValidator_Fixture, testAddOneValidTouch) {
    auto result = validator->checkNewValue(20);
    //
    EXPECT_EQ(validator->getCurrIsTouched(), true);
    EXPECT_EQ(validator->getPrevIsTouched(), false);
    EXPECT_EQ(validator->getPrevPrevIsTouched(), false);
    //
    EXPECT_EQ(validator->getCurrIsReleased(), false);
    EXPECT_EQ(validator->getPrevIsReleased(), false);
    EXPECT_EQ(validator->getPrevPrevIsReleased(), false);
    //
    EXPECT_EQ(result, CapacitiveTouch_Actions::ACTION_STANDBY);
    EXPECT_EQ(validator->getStateIsTouched(), false);

}

TEST_F(PinStateValidator_Fixture, testAddTwoValidTouch) {
    validator->checkNewValue(20);
    auto result = validator->checkNewValue(18);
    //
    EXPECT_EQ(validator->getCurrIsTouched(), true);
    EXPECT_EQ(validator->getPrevIsTouched(), true);
    EXPECT_EQ(validator->getPrevPrevIsTouched(), false);
    //
    EXPECT_EQ(validator->getCurrIsReleased(), false);
    EXPECT_EQ(validator->getPrevIsReleased(), false);
    EXPECT_EQ(validator->getPrevPrevIsReleased(), false);
    //
    EXPECT_EQ(result, CapacitiveTouch_Actions::ACTION_STANDBY);
    EXPECT_EQ(validator->getStateIsTouched(), false);

}

TEST_F(PinStateValidator_Fixture, testAddTwoValidRelease) {
    validator->checkNewValue(80);
    auto result = validator->checkNewValue(98);
    //
    EXPECT_EQ(validator->getCurrIsTouched(), false);
    EXPECT_EQ(validator->getPrevIsTouched(), false);
    EXPECT_EQ(validator->getPrevPrevIsTouched(), false);
    //
    EXPECT_EQ(validator->getCurrIsReleased(), true);
    EXPECT_EQ(validator->getPrevIsReleased(), true);
    EXPECT_EQ(validator->getPrevPrevIsReleased(), false);
    //
    EXPECT_EQ(result, CapacitiveTouch_Actions::ACTION_STANDBY);
    EXPECT_EQ(validator->getStateIsTouched(), false);

}

TEST_F(PinStateValidator_Fixture, testAddOneInvalidAndTwoValidTouchs) {
    validator->checkNewValue(33);
    validator->checkNewValue(18);
    auto result = validator->checkNewValue(22);
    //
    EXPECT_EQ(validator->getCurrIsTouched(), true);
    EXPECT_EQ(validator->getPrevIsTouched(), true);
    EXPECT_EQ(validator->getPrevPrevIsTouched(), false);
    //
    EXPECT_EQ(validator->getCurrIsReleased(), false);
    EXPECT_EQ(validator->getPrevIsReleased(), false);
    EXPECT_EQ(validator->getPrevPrevIsReleased(), false);
    //
    EXPECT_EQ(result, CapacitiveTouch_Actions::ACTION_STANDBY);
    EXPECT_EQ(validator->getStateIsTouched(), false);

}

TEST_F(PinStateValidator_Fixture, testAddOneInvalidAndThreeValidTouchs) {
    validator->checkNewValue(33);
    validator->checkNewValue(18);
     validator->checkNewValue(22);
    auto result = validator->checkNewValue(21);
    //
    EXPECT_EQ(validator->getCurrIsTouched(), true);
    EXPECT_EQ(validator->getPrevIsTouched(), true);
    EXPECT_EQ(validator->getPrevPrevIsTouched(), true);
    //
    EXPECT_EQ(validator->getCurrIsReleased(), false);
    EXPECT_EQ(validator->getPrevIsReleased(), false);
    EXPECT_EQ(validator->getPrevPrevIsReleased(), false);
    //
    EXPECT_EQ(result, CapacitiveTouch_Actions::ACTION_TOUCH_VALIDATED);
    EXPECT_EQ(validator->getStateIsTouched(), true);

}

TEST_F(PinStateValidator_Fixture, testAddTwoValidTouchAndOneInvalid) {
    validator->checkNewValue(20);
    validator->checkNewValue(18);
    auto result = validator->checkNewValue(33);
    //
    EXPECT_EQ(validator->getCurrIsTouched(), false);
    EXPECT_EQ(validator->getPrevIsTouched(), true);
    EXPECT_EQ(validator->getPrevPrevIsTouched(), true);
    //
    EXPECT_EQ(validator->getCurrIsReleased(), false);
    EXPECT_EQ(validator->getPrevIsReleased(), false);
    EXPECT_EQ(validator->getPrevPrevIsReleased(), false);
    //
    EXPECT_EQ(result, CapacitiveTouch_Actions::ACTION_STANDBY);
    EXPECT_EQ(validator->getStateIsTouched(), false);

}

TEST_F(PinStateValidator_Fixture, testAddThreeValidTouch) {
    validator->checkNewValue(20);
    validator->checkNewValue(21);
    auto result = validator->checkNewValue(18);
    //
    EXPECT_EQ(validator->getCurrIsTouched(), true);
    EXPECT_EQ(validator->getPrevIsTouched(), true);
    EXPECT_EQ(validator->getPrevPrevIsTouched(), true);
    //
    EXPECT_EQ(validator->getCurrIsReleased(), false);
    EXPECT_EQ(validator->getPrevIsReleased(), false);
    EXPECT_EQ(validator->getPrevPrevIsReleased(), false);
    //
    EXPECT_EQ(result, CapacitiveTouch_Actions::ACTION_TOUCH_VALIDATED);
    EXPECT_EQ(validator->getStateIsTouched(), true);
    //

}

TEST_F(PinStateValidator_Fixture, testAddThreeValidRelease) {
    validator->checkNewValue(89);
    validator->checkNewValue(83);
    auto result = validator->checkNewValue(68);
    //
    EXPECT_EQ(validator->getCurrIsTouched(), false);
    EXPECT_EQ(validator->getPrevIsTouched(), false);
    EXPECT_EQ(validator->getPrevPrevIsTouched(), false);
    //
    EXPECT_EQ(validator->getCurrIsReleased(), true);
    EXPECT_EQ(validator->getPrevIsReleased(), true);
    EXPECT_EQ(validator->getPrevPrevIsReleased(), true);
    //
    EXPECT_EQ(result, CapacitiveTouch_Actions::ACTION_STANDBY); // STANDBY BECAUSE NO TOUCH HAS BEEN MADE
    EXPECT_EQ(validator->getStateIsTouched(), false);
    //

}

TEST_F(PinStateValidator_Fixture, testAddThreeValidReleaseAfterThreeValidTouchs) {
    validator->checkNewValue(12);
    validator->checkNewValue(13);
    validator->checkNewValue(15);
    validator->checkNewValue(89);
    validator->checkNewValue(86);
    auto result = validator->checkNewValue(82);
    //
    EXPECT_EQ(validator->getCurrIsTouched(), false);
    EXPECT_EQ(validator->getPrevIsTouched(), false);
    EXPECT_EQ(validator->getPrevPrevIsTouched(), false);
    //
    EXPECT_EQ(validator->getCurrIsReleased(), true);
    EXPECT_EQ(validator->getPrevIsReleased(), true);
    EXPECT_EQ(validator->getPrevPrevIsReleased(), true);
    //
    EXPECT_EQ(result, CapacitiveTouch_Actions::ACTION_RELEASE_VALIDATED); // STANDBY BECAUSE NO TOUCH HAS BEEN MADE
    EXPECT_EQ(validator->getStateIsTouched(), false);
    //

}

TEST_F(PinStateValidator_Fixture, testAddFourValidTouch) {
    validator->checkNewValue(20);
    validator->checkNewValue(21);
    validator->checkNewValue(12);
    auto result = validator->checkNewValue(18);
    //
    EXPECT_EQ(validator->getCurrIsTouched(), true);
    EXPECT_EQ(validator->getPrevIsTouched(), true);
    EXPECT_EQ(validator->getPrevPrevIsTouched(), true);
    //
    EXPECT_EQ(validator->getCurrIsReleased(), false);
    EXPECT_EQ(validator->getPrevIsReleased(), false);
    EXPECT_EQ(validator->getPrevPrevIsReleased(), false);
    //
    EXPECT_EQ(result, CapacitiveTouch_Actions::ACTION_STANDBY);
    EXPECT_EQ(validator->getStateIsTouched(), true);
}