//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_ILEDBOARDSMANAGER_H
#define GONZYPROJECT_ILEDBOARDSMANAGER_H

#include "LedBoard.h"
#include "LedBoard_Store_Interface.h"
#include "LightStrategy_Factory.h"
#include "SpecialEffect_Factory.h"
#include "BlinkHighPriorityMessages.h"
#include "Debug_Helper.h"
#include <vector>

#ifndef IN_TESTING
#else
#include "../test/Fake_Arduino.h"
#endif

/**
 * @brief   Class which contains the references of store.
 *          Any trigger of board or change lightStrategy should be passed in this class
 *
 */
class LedBoardsManager {
public:
    explicit LedBoardsManager(
            LedBoard_Store_Interface *ledBoardStore,
            LightStrategy_Factory *lightStrategyFactory,
            SpecialEffect_Factory *specialEffectFactory,
            Debug_Helper *debugHelper
    ) {
        _debugHelper = debugHelper;
        _ledBoardStore = ledBoardStore;
        _ledBoards = _ledBoardStore->getLedBoards();
        _specialEffectFactory = specialEffectFactory;
        _specialEffectStrategy = _specialEffectFactory->makeStromboscopeSpecialEffect_Strategy(this);

    }

    virtual void init() = 0;

    virtual void show() = 0;

    virtual void showGlobally(CRGB color) = 0;

    virtual void reinitBoardsLightStrategies() {
        for (auto ledBoard: _ledBoards) {
            ledBoard->reinitLightStrategy();
        }
    }

    /**
     * Update the current time value and store the value. This will serve for updating all strategies which need a specific timing.
     * @param currentTime
     */
    virtual void update(unsigned long currentTime) {
        _currentTime = currentTime;
        _specialEffectStrategy->updateValues(_currentTime);
        for (auto ledBoard: _ledBoards) {
            ledBoard->updateValues(_currentTime);
        }
    };

    /**
     * Boards often need to call methods inside the manager, so we pass a reference of the manager to the boards
     */
    void giveAllBoardsReferenceOfManager() {
        for (auto board: _ledBoards) {
            board->giveReferenceManager(this);
        }
    }

    virtual void setShiftState(bool newState) {
        _isInShiftState = newState;
    }

    virtual void triggerOnBoard(uint8_t boardIndex, LIGHT_STRATEGIES strategy, CRGB color) {
        try {
            _ledBoards.at(boardIndex)->triggerOn(strategy, color);
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

    /**
     * Show a blocking blink. No other operation can be made during this, so use carefully, and avoid in loop.
     * @param errorMessage
     */
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
                showQuickBlink(CRGB::Orange);
                break;
            default:
                break;
        }
    }

    /**
     * QuickBlink can be useful for debugging purposes
     * @param color
     */
    virtual void showQuickBlink(CRGB color) {
        uint8_t LOOPS = 2;
        for (int i = 0; i < LOOPS; i++) {
            showGlobally(color);
            delay(100);
            showGlobally(CRGB::Black);
            delay(100);
        }
    }

    virtual void showIntermittentBlink(CRGB color) {
        uint8_t LOOPS = 3;
        for (int i = 0; i < LOOPS; i++) {
            showGlobally(color);
            delay(200);
            showGlobally(CRGB::Black);
            delay(200);
        }
    }

    virtual bool getShiftState() {
        return _isInShiftState;
    }

    virtual void setShiftColor(CRGB color) {
        _shiftColor = color;
    }

    virtual CRGB getShiftColor() {
        return _shiftColor;
    }

    Debug_Helper *getDebugHelper() {
        return _debugHelper;
    }

    virtual void setLightStrategyForChannel(uint8_t channel, LIGHT_STRATEGIES strategy, CRGB channelColor) {
        _channelStrategies[channel] = strategy;
        _channelColors[channel] = channelColor;
    }

    virtual void setSpecialEffectStrategyForChannel(uint8_t channel, SPECIAL_EFFECT_STRATEGY specialEffectStrategy) {
        _channelSpecialEffectsStrategies[channel] = specialEffectStrategy;
    }

    LIGHT_STRATEGIES getLightStrategyAssociatedWithChannel(uint8_t channel) {
        return _channelStrategies[channel];
    }

    CRGB getColorAssociatedWithChannel(uint8_t channel) {
        return _channelColors[channel];
    }

    SPECIAL_EFFECT_STRATEGY getSpecialEffectStrategyAssociatedWithChannel(uint8_t channel) {
        return _channelSpecialEffectsStrategies[channel];
    }

    virtual void triggerOnSpecialEffect(byte channel, byte note, byte velocity) {
        // we get the special effect corresponding to the channel
        auto specialEffectStrategy = getSpecialEffectStrategyAssociatedWithChannel(channel);
        //
        String message{">ACTIVATION of Special Effect Id: "};
        message += (int) specialEffectStrategy;
        _debugHelper->add(message);
        //
        changeSpecialEffectStrategy(specialEffectStrategy);
        _specialEffectStrategy->reinit();
        _specialEffectStrategy->triggerOn(note, velocity);
    }

    virtual void triggerOffSpecialEffect(byte channel, byte note, byte velocity) {
        _specialEffectStrategy->triggerOff(note, velocity);

    }

    virtual void changeSpecialEffectStrategy(SPECIAL_EFFECT_STRATEGY newSpecialEffect) {
        switch (newSpecialEffect) {
            case SPECIAL_EFFECT_STRATEGY::NO_SPECIAL_EFFECT:
                delete _specialEffectStrategy;
                _specialEffectStrategy = _specialEffectFactory->makeNoSpecialEffect_Strategy(this);
                break;
            case SPECIAL_EFFECT_STRATEGY::SPECIAL_EFFECT_STROMBOSCOPE:
                delete _specialEffectStrategy;
                _specialEffectStrategy = _specialEffectFactory->makeStromboscopeSpecialEffect_Strategy(this);
                break;
            default:
                _debugHelper->add("ERROR ! Unknown special effect strategy");
                break;
        }

    }

    virtual SpecialEffects_Strategy *getSpecialEffectStrategy() {
        return _specialEffectStrategy;
    }

protected:
    unsigned long _currentTime{};
    //
    SpecialEffect_Factory *_specialEffectFactory;
    SpecialEffects_Strategy *_specialEffectStrategy;
    //
    Debug_Helper *_debugHelper;
    CRGB _shiftColor = CRGB::Green;
    LedBoard_Store_Interface *_ledBoardStore;
    std::vector<LedBoard *> _ledBoards;

    SPECIAL_EFFECT_STRATEGY _channelSpecialEffectsStrategies[17]{SPECIAL_EFFECT_STRATEGY::NO_SPECIAL_EFFECT};
    LIGHT_STRATEGIES _channelStrategies[17]{LIGHT_STRATEGIES::NO_LIGHT_STRATEGY};
    CRGB _channelColors[17]{CRGB::Black};
    bool _isInShiftState = false;

};

#endif //GONZYPROJECT_ILEDBOARDSMANAGER_H