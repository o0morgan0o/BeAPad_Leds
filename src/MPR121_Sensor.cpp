//
// Created by morgan on 5/12/2022.
//

#include "MPR121_Sensor.h"

void MPR121_Sensor::create() {
    _cap = new Adafruit_MPR121();
}

bool MPR121_Sensor::begin() {
    return _cap->begin(0x5A);
}

uint16_t MPR121_Sensor::getTouched() {
    return _cap->touched();
}

void MPR121_Sensor::setThresholds(uint8_t touch, uint8_t release) {
    _cap->setThresholds(touch, release);

}