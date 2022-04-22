//
// Created by morgan on 4/21/2022.
//

#include "ConcreteLedBoardsManager.h"

ConcreteLedBoardsManager::ConcreteLedBoardsManager(const std::vector<ILedBoard*>& ledBoards) : ILedBoardsManager(ledBoards) {

}

void ConcreteLedBoardsManager::init() {
    // Creation of FastLed multiple arrays
    FastLED.addLeds<NEOPIXEL, 13>(ledStrip1, 9);
    FastLED.addLeds<NEOPIXEL, 12>(ledStrip2, 9);
    FastLED.addLeds<NEOPIXEL, 14>(ledStrip3, 9);
    FastLED.addLeds<NEOPIXEL, 27>(ledStrip4, 9);
    FastLED.addLeds<NEOPIXEL, 26>(ledStrip5, 9);
    FastLED.addLeds<NEOPIXEL, 25>(ledStrip6, 9);
    FastLED.addLeds<NEOPIXEL, 33>(ledStrip7, 9);
    FastLED.addLeds<NEOPIXEL, 32>(ledStrip8, 9);
    //
    // we pass for each ledstrip (board) its part of the array
    // numbers should be the same than above
    _ledBoards.at(0)->init(ledStrip1, 13);
    _ledBoards.at(1)->init(ledStrip2, 12);
    _ledBoards.at(2)->init(ledStrip3, 14);
    _ledBoards.at(3)->init(ledStrip4, 27);
    _ledBoards.at(4)->init(ledStrip5, 26);
    _ledBoards.at(5)->init(ledStrip6, 25);
    _ledBoards.at(6)->init(ledStrip7, 33);
    _ledBoards.at(7)->init(ledStrip8, 32);

}

void ConcreteLedBoardsManager::lightAll() {
    for(auto ledBoard : _ledBoards){
        ledBoard->command(LightCommands::LIGHT_ON);

    }

}

void ConcreteLedBoardsManager::update(unsigned long currentTime) {
    for(auto ledBoard : _ledBoards){
        ledBoard->update(currentTime);
    }

}

void ConcreteLedBoardsManager::show() {
    for(auto ledBoard: _ledBoards){
        ledBoard->show();
    }

}

void ConcreteLedBoardsManager::setRandomColorForEachBoard() {

}