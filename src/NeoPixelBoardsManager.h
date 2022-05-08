//
// Created by morgan on 5/8/2022.
//

#ifndef PLATFORMIO_PROGRAM_NEOPIXELBOARDSMANAGER_H
#define PLATFORMIO_PROGRAM_NEOPIXELBOARDSMANAGER_H

#include "LedBoardsManager.h"

class NeoPixelBoardsManager : public LedBoardsManager {
public:
    NeoPixelBoardsManager(
            LedBoard_Store_Interface *ledBoardStore,
            LightStrategy_Factory *lightStrategyFactory
    ) : LedBoardsManager(ledBoardStore, lightStrategyFactory) {}

    void init() override {
        for (auto board: _ledBoards) {
            board->initBoard();
        }
    }

    void show() override {
        for (auto board: _ledBoards) {
            board->show();
        }

    }

    void showBaseColor() override {
        for (auto ledBoard: _ledBoards) {
            ledBoard->showBaseColor();
            ledBoard->show();
        }
    }

    void showGlobally(CRGB color) override {
        for (auto board: _ledBoards) {
            board->showGlobalColor(color);
        }
    }
};

#endif //PLATFORMIO_PROGRAM_NEOPIXELBOARDSMANAGER_H