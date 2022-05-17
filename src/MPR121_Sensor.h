//
// Created by morgan on 5/12/2022.
//

#ifndef PLATFORMIO_PROGRAM_MPR121_SENSOR_H
#define PLATFORMIO_PROGRAM_MPR121_SENSOR_H

#include "Capacitive_Sensor.h"
#include "Adafruit_MPR121.h"

class MPR121_Sensor : public Capacitive_Sensor {
public:
    void create() override;

    bool begin() override;

    void setThresholds(uint8_t touch, uint8_t release) override;

    uint16_t getTouched() override;

private:
    Adafruit_MPR121 *_cap{};
};

#endif //PLATFORMIO_PROGRAM_MPR121_SENSOR_H