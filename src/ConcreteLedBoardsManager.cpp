//
// Created by morgan on 4/21/2022.
//

#include "ConcreteLedBoardsManager.h"

ConcreteLedBoardsManager::ConcreteLedBoardsManager(const std::vector<ILedBoard *> &ledBoards) : ILedBoardsManager(ledBoards) {

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
    _ledBoards.at(0)->init(ledStrip1, 13, this);
    _ledBoards.at(1)->init(ledStrip2, 12, this);
    _ledBoards.at(2)->init(ledStrip3, 14, this);
    _ledBoards.at(3)->init(ledStrip4, 27, this);
    _ledBoards.at(4)->init(ledStrip5, 26, this);
    _ledBoards.at(5)->init(ledStrip6, 25, this);
    _ledBoards.at(6)->init(ledStrip7, 33, this);
    _ledBoards.at(7)->init(ledStrip8, 32, this);

}

void ConcreteLedBoardsManager::lightAll(uint8_t r, uint8_t g, uint8_t b) {
    for (auto ledBoard: _ledBoards) {
        currentGlobalColor.setRGB(r,g,b);
        ledBoard->command(LightCommands::LIGHT_ON);
    }
}

void ConcreteLedBoardsManager::update(unsigned long currentTime) {
    for (auto ledBoard: _ledBoards) {
        ledBoard->update(currentTime);
    }

}

void ConcreteLedBoardsManager::show() {
    for (auto ledBoard: _ledBoards) {
        ledBoard->show();
    }

}

void ConcreteLedBoardsManager::setRandomColorForEachBoard() {

}

void ConcreteLedBoardsManager::forceLightOff() {
    for (auto ledBoard: _ledBoards) {
        ledBoard->command(LightCommands::LIGHT_OFF);
    }

}

const CRGB &ConcreteLedBoardsManager::getCurrentGlobalColor() {
    return currentGlobalColor;
}

void ConcreteLedBoardsManager::showSuccessSignal() {
    for (uint8_t i = 0; i < 4; i++) {
        for (auto ledBoard: _ledBoards) {
            ledBoard->command(LightCommands::LIGHT_SUCCESS);
        }
        show();
        delay(200);
        for(auto ledBoard: _ledBoards){
            ledBoard->command(LightCommands::LIGHT_OFF);
        }
        show();
        delay(200);
    }

}

void ConcreteLedBoardsManager::showErrorSignal() {
    for (uint8_t i = 0; i < 4; i++) {
        for (auto ledBoard: _ledBoards) {
            ledBoard->command(LightCommands::LIGHT_ERROR);
        }
        show();
        delay(200);
        for (auto ledBoard: _ledBoards) {
            ledBoard->command(LightCommands::LIGHT_OFF);
        }
        show();
        delay(200);
    }

}