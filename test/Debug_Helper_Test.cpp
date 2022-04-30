//
// Created by morgan on 4/24/2022.
//
#define IN_TESTING

#include <memory>
#include <gtest/gtest.h>
#include "../src/Debug_Helper.h"

TEST(FakeStringTest, testEqualStrings) {
    String message1{"myMessage"};
    String message2{"myMessage"};
    EXPECT_EQ(message1 == message2, true);
    EXPECT_EQ(message1 , "myMessage");
    String message3{"myMessage"};
    String message4{"myMessageOther"};
    EXPECT_EQ(message4 == "out", false);
    EXPECT_EQ(message3 == message4, false);
}

TEST(debugHelperTest, init){
    Debug_Helper debugHelper;
    auto result = debugHelper.getString();
    EXPECT_EQ(result == "DEBUG_STRING<br/>", true);
}

TEST(debugHelperAddTest, shouldHadMessageCorrectly) {
    Debug_Helper debugHelper;
    const String message{"myMessage"};
    debugHelper.add(String{"myMessage"});
    auto result = debugHelper.getString();
    EXPECT_EQ(result == "DEBUG_STRING<br/>myMessage<br/>", true);
    EXPECT_EQ(result == "shouldNot", false);
}

TEST(debugHelperTest, reinit){
    Debug_Helper debugHelper;
    debugHelper.add(String{"myMessage"});
    EXPECT_EQ(debugHelper.getString() == "DEBUG_STRING<br/>myMessage<br/>", true);
    debugHelper.reinit();
    EXPECT_EQ(debugHelper.getString() == "DEBUG_STRING<br/>", true);
}

TEST(debugHelperTest, addMutliple){
    Debug_Helper debugHelper;
    debugHelper.add(String{"myMessage"});
    debugHelper.add(String{"anotherMessage"});
    EXPECT_EQ(debugHelper.getString() == "DEBUG_STRING<br/>myMessage<br/>anotherMessage<br/>", true);

}