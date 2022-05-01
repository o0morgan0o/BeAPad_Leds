//
// Created by morgan on 5/1/2022.
//

#ifndef PLATFORMIO_PROGRAM_PINSTATEVALIDATOR_H
#define PLATFORMIO_PROGRAM_PINSTATEVALIDATOR_H

#include <cstdint>
#include "CapacitiveTouch_Actions.h"

class PinStateValidator {
public:
    PinStateValidator() {

    }

    void init(uint8_t *touchThreshold, uint8_t *releaseThreshold) {
        _touchThreshold = touchThreshold;
        _releaseThreshold = releaseThreshold;
        //
        _currIsTouched = false;
        _prevIsTouched = false;
        _prevPrevIsTouched = false;
        //
        _currIsReleased = false;
        _prevIsReleased = false;
        _prevPrevIsReleased = false;
        //
        _stateIsTouched = false; // set to false because nautral state is released
    }

    CapacitiveTouch_Actions checkNewValue(const uint16_t newValue) {
        _prevPrevIsTouched = _prevIsTouched;
        _prevIsTouched = _currIsTouched;
        //
        _prevPrevIsReleased = _prevIsReleased;
        _prevIsReleased = _currIsReleased;
        //
        _currIsTouched = newValue < *_touchThreshold ?: false;
        _currIsReleased = newValue > *_releaseThreshold ?: false;
        //
        auto result = checkAction();
        //
        //

        return result;
    }

private:
    CapacitiveTouch_Actions checkAction() {
        if (_currIsTouched && _prevIsTouched && _prevPrevIsTouched && !_stateIsTouched) {
            _stateIsTouched = true;
            return CapacitiveTouch_Actions::ACTION_TOUCH_VALIDATED;
        }
        if (_currIsReleased && _prevIsReleased && _prevPrevIsReleased && _stateIsTouched) {
            _stateIsTouched = false;
            return CapacitiveTouch_Actions::ACTION_RELEASE_VALIDATED;
        }
        return CapacitiveTouch_Actions::ACTION_STANDBY;

    }

private:
    uint8_t *_touchThreshold;
    uint8_t *_releaseThreshold;
public:
    bool getCurrIsTouched() const { return _currIsTouched; }

    bool getPrevIsTouched() const { return _prevIsTouched; }

    bool getPrevPrevIsTouched() const { return _prevPrevIsTouched; }

    bool getCurrIsReleased() const { return _currIsReleased; }

    bool getPrevIsReleased() const { return _prevIsReleased; }

    bool getPrevPrevIsReleased() const { return _prevPrevIsReleased; }

    bool getStateIsTouched() const { return _stateIsTouched; }

private:
    bool _currIsTouched;
    bool _prevIsTouched;
    bool _prevPrevIsTouched;

    bool _currIsReleased;
    bool _prevIsReleased;
    bool _prevPrevIsReleased;

    bool _stateIsTouched;

};

#endif //PLATFORMIO_PROGRAM_PINSTATEVALIDATOR_H