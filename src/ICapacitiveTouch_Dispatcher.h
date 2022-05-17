//
// Created by morgan on 5/1/2022.
//

#ifndef PLATFORMIO_PROGRAM_ICAPACITIVETOUCH_DISPATCHER_H
#define PLATFORMIO_PROGRAM_ICAPACITIVETOUCH_DISPATCHER_H

#include "Midi_Handler.h"

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
    }

    virtual void setThresholds(uint8_t touch, uint8_t release) = 0;

protected:
    LIGHT_STRATEGIES _touchTriggerLightStrategies[12]{LIGHT_STRATEGIES::NO_LIGHT_STRATEGY};
    //
    Midi_Handler *_midiHandler;
    LedBoardsManager *_manager;
    Debug_Helper *_debugHelper;
};

#endif //PLATFORMIO_PROGRAM_ICAPACITIVETOUCH_DISPATCHER_H