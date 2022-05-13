//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_ILEDBOARDSMANAGER_H
#define GONZYPROJECT_ILEDBOARDSMANAGER_H

#include "LedBoard.h"
#include "LedStrip_Holder_Interface.h"
#include "LedBoard_Store_Interface.h"
#include "LightStrategy_Factory.h"
#include "BlinkHighPriorityMessages.h"
#include <vector>

#ifndef IN_TESTING
#else
#include "../test/Fake_Arduino.h"
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

    virtual void changeStrategyOnBoard(uint8_t boardIndex, LIGHT_STRATEGIES strategy) {
        _ledBoards.at(boardIndex)->changeLightStrategy(strategy);
    }

    virtual void update(unsigned long currentTime) {
        for (auto ledBoard: _ledBoards) {
            ledBoard->updateValues(currentTime);
        }
    };

    void giveAllBoardsReferenceOfManager() {
        for (auto board: _ledBoards) {
            board->giveReferenceManager(this);
        }
    }

    virtual void setShiftState(bool newState) {
        _isInShiftState = newState;
    }

    virtual void triggerOnBoard(uint8_t boardIndex) {
        try {
            _ledBoards.at(boardIndex)->triggerOn();
        } catch (std::exception &e) {
            showBlinkHighPriorityMessage(BlinkHighPriorityMessages::TRIGGER_BOARD_ERROR);
        }
    }

    virtual void triggerOnBoard(uint8_t boardIndex, LIGHT_STRATEGIES strategy) {
        try {
            _ledBoards.at(boardIndex)->triggerOn(strategy);
        } catch (std::exception &e) {
            showBlinkHighPriorityMessage(BlinkHighPriorityMessages::TRIGGER_BOARD_ERROR);
        }
    }

    virtual void triggerOffBoard(uint8_t boardIndex) {
        try {
            _ledBoards.at(boardIndex)->triggerOff();
        } catch (std::exception &e) {
            showBlinkHighPriorityMessage(BlinkHighPriorityMessages::TRIGGER_BOARD_ERROR);
        }
    }

    virtual void setBoardBaseColor(uint8_t boardIndex, CRGB color) {
        _ledBoards.at(boardIndex)->setBoardColor(color);
    }

    virtual void showBlinkHighPriorityMessage(BlinkHighPriorityMessages errorMessage) {
        switch (errorMessage) {
            case BlinkHighPriorityMessages::MPR121_SENSOR_NOT_FOUND:
                showIntermittentBlink(CRGB::Red);
                break;
            case BlinkHighPriorityMessages::TRIGGER_BOARD_ERROR:
//                showIntermittentBlink(CRGB::Orange);
                break;
            case BlinkHighPriorityMessages::RTP_CONNECTION_SUCCESS:
                showIntermittentBlink(CRGB::Green);
                break;
            case BlinkHighPriorityMessages::RTP_CONNECTION_LOST:
                showIntermittentBlink(CRGB::Yellow);
                break;
            case BlinkHighPriorityMessages::SHOW_END_OF_SETUP_MESSAGE:
                showQuickBlink(CRGB::Yellow);
                showQuickBlink(CRGB::Green);
                break;
            default:
                break;
        }
    }

    virtual void showQuickBlink(CRGB color) {
        uint8_t LOOPS = 2;
        for (int i = 0; i < LOOPS; i++) {
            showGlobally(color);
            delay(200);
            showGlobally(CRGB::Black);
            delay(200);
        }
    }

    virtual void showIntermittentBlink(CRGB color) {
        uint8_t LOOPS = 4;
        for (int i = 0; i < LOOPS; i++) {
            showGlobally(color);
            delay(500);
            showGlobally(CRGB::Black);
            delay(500);
        }
    }

    virtual void showBaseColor() = 0;

    virtual bool getShiftState() { return _isInShiftState; }

    virtual void setShiftColor(CRGB color) {
        _shiftColor = color;
    }

    virtual CRGB getShiftColor() { return _shiftColor; }

//    virtual void setRandomColorForEachBoard() = 0;

//    virtual const CRGB &getCurrentGlobalColor() = 0;


protected:
    CRGB _shiftColor = CRGB::White;
    LedBoard_Store_Interface *_ledBoardStore;
    std::vector<LedBoard *> _ledBoards;
    LightStrategy_Factory *_lightStrategyFactory;
    bool _isInShiftState = false;

};

#endif //GONZYPROJECT_ILEDBOARDSMANAGER_H