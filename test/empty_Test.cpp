#include <gtest/gtest.h>
#define  IN_TESTING
#include "../src/Board.h"
#include "FakeBoard.h"
#include "FakeConcreteLedBoardManager.h"
#include <vector>
#include <memory>

TEST(myTest, testFirst){
    EXPECT_EQ(1,1);
    FakeBoard fakeBoard;

//    Board board{};
//    EXPECT_EQ(board._var, 10);
}

TEST(BoardCreation, testManagerGetAllCreatedBoards){
    auto ledboards = std::vector<ILedBoard*>();
    ledboards.emplace_back(new FakeBoard());
    ledboards.emplace_back(new FakeBoard());
    ledboards.emplace_back(new FakeBoard());
    ledboards.emplace_back(new FakeBoard());
    ledboards.emplace_back(new FakeBoard());
    ledboards.emplace_back(new FakeBoard());
    ledboards.emplace_back(new FakeBoard());
    ledboards.emplace_back(new FakeBoard());
    auto fakeLedBoardsManager = std::make_unique<FakeConcreteLedBoardManager>(ledboards);
    //
//    EXPECT_EQ(fakeLedBoardsManager->getLedBoardsVector().size(), 8);
}