cmake_minimum_required(VERSION 3.15)
project(GONZY_PROJECT_TEST VERSION 0.0.1)
add_subdirectory(googletest-release)
include_directories(googletest-release)

enable_testing()

#find_package(Thread REQUIRED)
list(FILTER SOURCES_CPP_FILES EXCLUDE REGEX ${PROJECT_SOURCE_DIR}/*_Test.cpp)
file(GLOB_RECURSE TEST_FILES *_Test.cpp)
message("RESULT OF SOURCES FILES RECURSE FIND :")
message("${SOURCES_CPP_FILES}")

set(TEST_SOURCES ${TEST_FILES})
set(SOURCE_FILES
#        FakeBoard.h FakeBoard.cpp
#        FakeConcreteLedBoardManager.h FakeConcreteLedBoardManager.cpp
#        Fake_CRGB.h Fake_CRGB.cpp
#        "../src/ConcreteLedBoardsManager.h" "../src/ConcreteLedBoardsManager.cpp"
        )


add_executable(allTests main-alltests.cpp ${TEST_FILES})

target_sources(allTests PRIVATE ${PRIVATE_SOURCES} ${TEST_SOURCES} ${SOURCE_FILES})
target_link_libraries(allTests PRIVATE gtest_main gmock_main ${GTEST_LIBRARIES})