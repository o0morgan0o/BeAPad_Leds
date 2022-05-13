//
// Created by morgan on 5/12/2022.
//

#ifndef PLATFORMIO_PROGRAM_CAPACITIVE_SENSOR_H
#define PLATFORMIO_PROGRAM_CAPACITIVE_SENSOR_H

#include <cstdint>

class Capacitive_Sensor {
public:
    Capacitive_Sensor() = default;
    virtual void create() = 0;

    virtual bool begin() = 0;

    virtual uint16_t getTouched() = 0;

};

#endif //PLATFORMIO_PROGRAM_CAPACITIVE_SENSOR_H