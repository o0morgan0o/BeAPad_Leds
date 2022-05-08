//
// Created by morgan on 4/21/2022.
//

#include "FastLedLedBoardsManager.h"

FastLedLedBoardsManager::FastLedLedBoardsManager(
        LedBoard_Store_Interface *ledBoardStore,
        LightStrategy_Factory *lightStrategyFactory
)
        : LedBoardsManager(ledBoardStore, lightStrategyFactory) {
}

//
void FastLedLedBoardsManager::init() {
    // we pass for each ledstrip (board) its part of the array
    //    _ledBoards.at(0)->giveReferenceManager(_ledBoardStore->ledStrip0, 23, this);

    _ledBoards.at(0)->giveReferenceManager(_ledBoardStore->ledStrip0, this);
    _ledBoards.at(1)->giveReferenceManager(_ledBoardStore->ledStrip1, this);
    _ledBoards.at(2)->giveReferenceManager(_ledBoardStore->ledStrip2, this);
    _ledBoards.at(3)->giveReferenceManager(_ledBoardStore->ledStrip3, this);
    _ledBoards.at(4)->giveReferenceManager(_ledBoardStore->ledStrip4, this);
    _ledBoards.at(5)->giveReferenceManager(_ledBoardStore->ledStrip5, this);
    _ledBoards.at(6)->giveReferenceManager(_ledBoardStore->ledStrip6, this);
    _ledBoards.at(7)->giveReferenceManager(_ledBoardStore->ledStrip7, this);

}

void FastLedLedBoardsManager::showGlobally(CRGB color) {
    FastLED.showColor(color);
}

void FastLedLedBoardsManager::show() {
    FastLED.show();
}

void FastLedLedBoardsManager::showBaseColor() {

}