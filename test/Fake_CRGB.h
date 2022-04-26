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
//        r = a.r;
//        g = a.g;
//        b = a.b;
//    }

    CRGB(const CRGB &a) {
        r = a.r;
        g = a.g;
        b = a.b;
    }

    CRGB(uint8_t r, uint8_t g, uint8_t b) {
        r = r;
        g = g;
        b = b;

    }

//    CRGB(const CRGB crgb) {
//
//    }

    uint8_t r{};
    uint8_t g{};
    uint8_t b{};

    static CRGB Black;
    static CRGB Green;
    static CRGB Red;
    static CRGB White;

    void setRGB(uint8_t _r, uint8_t _g, uint8_t _b) {
        r = _r;
        g = _g;
        b = _b;

    }

};

#endif //GONZY_PROJECT_TEST_FAKE_CRGB_H