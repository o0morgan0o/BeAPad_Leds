//
// Created by morgan on 4/23/2022.
//

#include "Fake_CRGB.h"

CRGB CRGB::Black{0, 0, 0};
CRGB CRGB::Green{0, 255, 0};
CRGB CRGB::Red{255, 0, 0};
CRGB CRGB::White{255, 255, 255};
CRGB CRGB::AliceBlue{0, 0, 255};
CRGB CRGB::Blue{0, 0, 255};
CRGB CRGB::Yellow{255, 255, 0};
CRGB CRGB::Orange(255, 165, 0);

CRGB blend(CRGB &p1, CRGB &p2,  uint8_t amountOfP2) {
    return CRGB::Blue;
}

CRGB blend(CRGB p1, CRGB p2, uint8_t amountOfP2) {
    return p1;
}

CRGB blend(const CRGB &p1, const CRGB &p2, uint8_t amountOfP1) {
    return p1;
}

CRGB blend(CRGB &p1, const CRGB &p2, uint8_t amountOfP1) {
    return p1;
}

CRGB blend(const CRGB &p1, CRGB &p2, uint8_t amountOfP1) {
    return p1;
}