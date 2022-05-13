//
// Created by morgan on 5/12/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKE_SENSOR_H
#define GONZY_PROJECT_TEST_FAKE_SENSOR_H
#define IN_TESTING

#include "../src/Capacitive_Sensor.h"

class Fake_Sensor : public Capacitive_Sensor {
public:
    void create() override {

    }

    bool begin() override {
        return true;
    }

    uint16_t getTouched() override {
        return _fake_value;
    }

    void setFakeValue(uint16_t fakeValue) {
        _fake_value = fakeValue;
    }

private:
    uint16_t _fake_value{0b0000000000000000};

};

#endif //GONZY_PROJECT_TEST_FAKE_SENSOR_H