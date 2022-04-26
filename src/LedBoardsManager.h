//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_ILEDBOARDSMANAGER_H
#define GONZYPROJECT_ILEDBOARDSMANAGER_H

#include "LedBoard.h"
#include "LedStrip_Holder_Interface.h"
#include "LedBoard_Store_Interface.h"
#include "LightStrategy_Factory.h"
#include <vector>

#ifndef IN_TESTING
#endif

class LedBoardsManager {
public:
    explicit LedBoardsManager(
            LedBoard_Store_Interface *ledBoardStore,
            LightStrategy_Factory *lightStrategyFactory
    ) {
        _ledBoardStore = ledBoardStore;
        _ledBoards = _ledBoardStore->getLedBoards();
        _lightStrategyFactory = lightStrategyFactory;

    }

    virtual void init() = 0;

    virtual void show() = 0;

    virtual void showGlobally(CRGB color) = 0;

    virtual void reinitBoardsLightStrategies() {
        for (auto ledBoard: _ledBoards) {
            ledBoard->reinitLightStrategy();
        }
    }


//    virtual void lightBoard(uint8_t boardIndex, LightStrategy _lightStrategy){
//
//    }

    virtual void lightCommandOnBoard(uint8_t boardIndex, LightCommands command) {
        _ledBoards.at(boardIndex)->command(command);
    }

    virtual void changeStrategyOnBoard(uint8_t boardIndex, LIGHT_STRATEGIES strategy) {
        _ledBoards.at(boardIndex)->changeLightStrategy(strategy);
    }

    //
    virtual void update(unsigned long currentTime) {
        for (auto ledBoard: _ledBoards) {
            ledBoard->update(currentTime);
        }
    };

    virtual void simulateTriggerOnBoard(uint8_t boardIndex){
        // TODO check if boardInde is a correct value
        _ledBoards.at(boardIndex)->trigger();

    }

    virtual void setBoardBaseColor(uint8_t boardIndex, uint8_t r, uint8_t g, uint8_t b) {
        _ledBoards.at(boardIndex)->setBoardColor(r, g, b);
    }

    virtual void setBoardBaseColor(uint8_t boardIndex, CRGB color) {
        _ledBoards.at(boardIndex)->setBoardColor(color);
    }
//
//    virtual void setRandomColorForEachBoard() = 0;
//
//    virtual const CRGB &getCurrentGlobalColor() = 0;
//
//    virtual void showSuccessSignal() = 0;
//
//    virtual void showErrorSignal() = 0;
//
protected:
    LedBoard_Store_Interface *_ledBoardStore;
    std::vector<LedBoard *> _ledBoards;
    LightStrategy_Factory *_lightStrategyFactory;

};

#endif //GONZYPROJECT_ILEDBOARDSMANAGER_H