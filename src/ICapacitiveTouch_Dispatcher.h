//
// Created by morgan on 5/1/2022.
//

#ifndef PLATFORMIO_PROGRAM_ICAPACITIVETOUCH_DISPATCHER_H
#define PLATFORMIO_PROGRAM_ICAPACITIVETOUCH_DISPATCHER_H

#include "Midi_Handler.h"
#include "PinStateValidator.h"

class ICapacitiveTouch_Dispatcher {
public:
    ICapacitiveTouch_Dispatcher(LedBoardsManager *manager, Midi_Handler *midiHandler, Debug_Helper *debugHelper) {
        _manager = manager;
        _midiHandler = midiHandler;
        _debugHelper = debugHelper;
    }

    virtual void begin() = 0;

    virtual void loop() = 0;

    virtual void setTriggerOnTouchLightStrategyOnBoard(uint8_t boardIndex, LIGHT_STRATEGIES strategy) {
        _touchTriggerLightStrategies[boardIndex] = strategy;
//        _ledBoards.at(boardIndex)->changeLightStrategy(strategy);
    }

    virtual void setTouchThreshold(uint8_t newThreshold) = 0;

    virtual void setReleaseThreshold(uint8_t newThreshold) = 0;

    virtual uint8_t getTouchThreshold() const = 0;

    virtual uint8_t getReleaseThreshold() const = 0;

protected:
    LIGHT_STRATEGIES _touchTriggerLightStrategies[12]{LIGHT_STRATEGIES::NO_LIGHT_STRATEGY};
    //
    uint8_t TOUCH_THRESHOLD = 35;
    uint8_t RELEASE_THRESHOLD = 40;
    //
    Midi_Handler *_midiHandler;
    LedBoardsManager *_manager;
    Debug_Helper *_debugHelper;
};

#endif //PLATFORMIO_PROGRAM_ICAPACITIVETOUCH_DISPATCHER_H