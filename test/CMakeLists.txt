cmake_minimum_required(VERSION 3.15)
project(GONZY_PROJECT_TEST VERSION 0.0.1)
add_subdirectory(googletest-release)
include_directories(googletest-release)

enable_testing()

#find_package(Thread REQUIRED)
file(GLOB_RECURSE SOURCES_CPP_FILES "../src/*.cpp")
file(GLOB_RECURSE HEADER_CPP_FILES "../src/*.h")
list(FILTER SOURCES_CPP_FILES EXCLUDE REGEX ${PROJECT_SOURCE_DIR}/*_Test.cpp)
file(GLOB_RECURSE TEST_FILES *_Test.cpp)

message("RESULT OF HEADER FILES RECURSE FIND :")
message("${HEADER_CPP_FILES}")

message("RESULT OF SOURCES FILES RECURSE FIND :")
message("${SOURCES_CPP_FILES}")

set(TEST_SOURCES ${TEST_FILES})
set(SOURCE_FILES
        FakeString.h
        FakeLedBoard.h FakeLedBoard.cpp
        FakeLedBoardStore.h FakeLedBoardStore.cpp
        Fake_CRGB.h Fake_CRGB.cpp
        FakeLedBoardManager.h FakeLedBoardManager.cpp
        FakeMidiKeyReceiver.h FakeMidiKeyReceiver.cpp
        Fake_MidiHandler.h Fake_MidiHandler.cpp
        Fake_Arduino.h Fake_Arduino.cpp
        Fake_Sensor.h Fake_Sensor.cpp
        )


add_executable(allTests main-alltests.cpp ${TEST_FILES})

target_sources(allTests PRIVATE
        ${PRIVATE_SOURCES}
        ${TEST_SOURCES}
        ${SOURCE_FILES}
#        ${HEADER_CPP_FILES}
        )
target_link_libraries(allTests PRIVATE
        gtest_main
        gmock_main
        ${GTEST_LIBRARIES}
#        ${SOURCES_CPP_FILES}
        )