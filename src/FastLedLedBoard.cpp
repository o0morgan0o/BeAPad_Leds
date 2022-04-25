//
// Created by morgan on 4/21/2022.
//

#include "FastLedLedBoard.h"
#include "LedBoardsManager.h"

FastLedLedBoard::FastLedLedBoard() : LedBoard() {
    _lightStrategy = new FullLightStrategy(this, 2000);
    _currentTime = 0.0;
}

void FastLedLedBoard::show() {

}