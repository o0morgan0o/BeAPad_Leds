//
// Created by morgan on 5/1/2022.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Debug_Helper.h"
#include "../src/CapacitiveTouch_Dispatcher.h"

struct CapacitiveTest_Fixture : public testing::Test {
    struct CapacitiveTouch_Dispatcher_Mock : public CapacitiveTouch_Dispatcher {
        CapacitiveTouch_Dispatcher_Mock(Midi_Handler *midiHandler, Debug_Helper *debugHelper)
                : CapacitiveTouch_Dispatcher(midiHandler, debugHelper) {

        }

    };

protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(CapacitiveTest_Fixture, testBasicRead) {
    auto debugHelper = new Debug_Helper();
    auto midiHandler
    auto capacitiveTouch = new CapacitiveTouch_Dispatcher_Mock()

}