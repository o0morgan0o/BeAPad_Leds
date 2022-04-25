//
// Created by morgan on 4/23/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKE_CRGB_H
#define GONZY_PROJECT_TEST_FAKE_CRGB_H

#include <cstdint>

class CRGB {
public:
    CRGB() = default;

//    CRGB(CRGB &a) {
//        _r = a._r;
//        _g = a._g;
//        _b = a._b;
//    }

    CRGB(const CRGB &a) {
        _r = a._r;
        _g = a._g;
        _b = a._b;
    }

    CRGB(uint8_t r, uint8_t g, uint8_t b) {
        _r = r;
        _g = g;
        _b = b;

    }

//    CRGB(const CRGB crgb) {
//
//    }

    uint8_t _r{};
    uint8_t _g{};
    uint8_t _b{};

};

#endif //GONZY_PROJECT_TEST_FAKE_CRGB_H