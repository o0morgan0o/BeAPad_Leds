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
    //
    // we pass for each ledstrip (board) its part of the array
    // numbers should be the same than above

    // TODO: TESTING !
//    _ledBoards.at(0)->giveReferenceManager(_ledBoardStore->ledStrip0, 23, this);
    _ledBoards.at(0)->giveReferenceManager(_ledBoardStore->ledStrip0, 13, this);
    //
    _ledBoards.at(1)->giveReferenceManager(_ledBoardStore->ledStrip1, 12, this);
    _ledBoards.at(2)->giveReferenceManager(_ledBoardStore->ledStrip2, 14, this);
    _ledBoards.at(3)->giveReferenceManager(_ledBoardStore->ledStrip3, 27, this);
    _ledBoards.at(4)->giveReferenceManager(_ledBoardStore->ledStrip4, 26, this);
    _ledBoards.at(5)->giveReferenceManager(_ledBoardStore->ledStrip5, 25, this);
    _ledBoards.at(6)->giveReferenceManager(_ledBoardStore->ledStrip6, 33, this);
    _ledBoards.at(7)->giveReferenceManager(_ledBoardStore->ledStrip7, 32, this);

}

void FastLedLedBoardsManager::showGlobally(CRGB color) {
    FastLED.showColor(color);
}

void FastLedLedBoardsManager::show() {
    FastLED.show();
}



//
//void FastLedLedBoardsManager::update(unsigned long currentTime) {
//    for (auto ledBoard: _ledBoards) {
//        ledBoard->update(currentTime);
//    }
//
//}
//
//
//}
//
//void FastLedLedBoardsManager::setRandomColorForEachBoard() {
//
//}
//
//void FastLedLedBoardsManager::forceLightOff() {
//    for (auto ledBoard: _ledBoards) {
//        ledBoard->command(LightCommands::LIGHT_OFF);
//    }
//
//}
//
//const CRGB &FastLedLedBoardsManager::getCurrentGlobalColor() {
//    return currentGlobalColor;
//}
//
//void FastLedLedBoardsManager::showSuccessSignal() {
//    for (uint8_t i = 0; i < 4; i++) {
//        for (auto ledBoard: _ledBoards) {
//            ledBoard->command(LightCommands::LIGHT_SUCCESS);
//        }
//        show();
//        delay(200);
//        for(auto ledBoard: _ledBoards){
//            ledBoard->command(LightCommands::LIGHT_OFF);
//        }
//        show();
//        delay(200);
//    }
//
//}
//
//void FastLedLedBoardsManager::showErrorSignal() {
//    for (uint8_t i = 0; i < 4; i++) {
//        for (auto ledBoard: _ledBoards) {
//            ledBoard->command(LightCommands::LIGHT_ERROR);
//        }
//        show();
//        delay(200);
//        for (auto ledBoard: _ledBoards) {
//            ledBoard->command(LightCommands::LIGHT_OFF);
//        }
//        show();
//        delay(200);
//    }
//
//}
//
//void FastLedLedBoardsManager::lightWhite() {
//    for(auto ledBoard: _ledBoards){
//        ledBoard->command(LightCommands::LIGHT_WHITE);
//    }
//    show();
//
//}