//
// Created by morgan on 4/24/2022.
//
#include <gtest/gtest.h>
#include <memory>
#include "../src/LogMessages_Store.h"

TEST(LogMessagesStore, emptyBuffer) {
    auto logMessagesStore = std::make_unique<LogMessages_Store>();
    EXPECT_EQ(logMessagesStore->getMessageLength(), 1);
}

TEST(LogMessageStore, getBufferAtInit) {
    auto logMessagesStore = std::make_unique<LogMessages_Store>();
    char result[logMessagesStore->getMessageLength()];
    logMessagesStore->populateChar(result);
    EXPECT_EQ(strlen(result), 0);
    EXPECT_EQ(*result, 0);
}

TEST(LogMessageStore, addMessage) {
    auto logMessagesStore = std::make_unique<LogMessages_Store>();
    logMessagesStore->addMessage("testString");
    char result[logMessagesStore->getMessageLength()];
    logMessagesStore->populateChar(result);
    EXPECT_EQ(logMessagesStore->getMessageLength(), 11);
    EXPECT_EQ(strcmp(result, "testString"), 0);
}

TEST(LogMessageTest, basicFunctions) {
    auto logMessagesStore = std::make_unique<LogMessages_Store>();
    logMessagesStore->addMessage("hello");
    logMessagesStore->addMessage("World");
    char result[logMessagesStore->getMessageLength()];
    logMessagesStore->populateChar(result);
    EXPECT_EQ(strcmp(result, "helloWorld"), 0);

}

TEST(LogMessageTest, addCharsWithSpace) {
    auto logMessagesStore = std::make_unique<LogMessages_Store>();
    logMessagesStore->addMessage("hello");
    logMessagesStore->addMessage(" World");
    char result[logMessagesStore->getMessageLength()];
    logMessagesStore->populateChar(result);
    EXPECT_EQ(strcmp(result, "hello World"), 0);

}