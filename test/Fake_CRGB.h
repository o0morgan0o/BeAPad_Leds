//
// Created by morgan on 4/23/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKE_CRGB_H
#define GONZY_PROJECT_TEST_FAKE_CRGB_H

#include <cstdint>

class CHSV {
public:
    CHSV(uint8_t _h, uint8_t _s, uint8_t _v) {
        h=_h;
        s=_s;
        v=_v;
    }

    uint8_t h{};
    uint8_t s{};
    uint8_t v{};
};

class CRGB {
public:
    CRGB() = default;

     explicit CRGB(CHSV chsv){
        r = chsv.h;
        g= chsv.s;
        b=chsv.v;
    }

    CRGB(const CRGB &a) {
        r = a.r;
        g = a.g;
        b = a.b;
    }

    CRGB(CRGB &a) {
        r = a.r;
        g = a.g;
        b = a.b;
    }

    CRGB &operator=(const CRGB &a) = default;

    CRGB &operator=(CRGB &a) = default;

    bool operator==(const CRGB& a) const{
        return (r==a.r && g==a.g && b==a.b);
    }

    CRGB(uint8_t r, uint8_t g, uint8_t b) {
        r = r;
        g = g;
        b = b;

    }

    uint8_t r{};
    uint8_t g{};
    uint8_t b{};

    static CRGB Black;
    static CRGB Green;
    static CRGB Red;
    static CRGB White;
    static CRGB AliceBlue;
    static CRGB Blue;
    static CRGB Yellow;
    static CRGB Orange;

    void setRGB(uint8_t _r, uint8_t _g, uint8_t _b) {
        r = _r;
        g = _g;
        b = _b;
    }

    void fadeToBlackBy(uint8_t f) {
        r -= f;
        g -= f;
        b -= b;
        if (r < 0) r = 0;
        if (g < 0) g = 0;
        if (b < 0) b = 0;
    }

};

CRGB blend(CRGB &p1, CRGB &p2, uint8_t amountOfP2);

#endif //GONZY_PROJECT_TEST_FAKE_CRGB_H