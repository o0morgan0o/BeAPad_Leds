#include <gtest/gtest.h>
#include "../src/Board.h"

TEST(myTest, testFirst){
    EXPECT_EQ(1,1);

    Board board{};
    EXPECT_EQ(board._var, 10);
}

TEST(BoardCreation, shouldCreate8BoardsAtStartup){

}