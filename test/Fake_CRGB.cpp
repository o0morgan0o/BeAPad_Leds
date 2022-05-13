//
// Created by morgan on 4/23/2022.
//

#include "Fake_CRGB.h"

CRGB CRGB::Black{0, 0, 0};
CRGB CRGB::Green{0, 255, 0};
CRGB CRGB::Red{255, 0, 0};
CRGB CRGB::White{255, 255, 255};
CRGB CRGB::AliceBlue{0,0,255};
CRGB CRGB::Blue{0,0,255};
CRGB CRGB::Yellow{255,255,0};

CRGB blend(CRGB &p1, CRGB &p2, uint8_t amountOfP2) {
    return p1;
}