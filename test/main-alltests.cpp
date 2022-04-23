#include <gtest/gtest.h>
#include <gmock/gmock.h>
#define IN_TESTING

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}