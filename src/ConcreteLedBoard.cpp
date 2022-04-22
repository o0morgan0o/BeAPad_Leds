//
// Created by morgan on 4/21/2022.
//

#include "ConcreteLedBoard.h"

ConcreteLedBoard::ConcreteLedBoard() : ILedBoard() {

}

void ConcreteLedBoard::init(CRGB *leds, uint8_t pixelPin) {
    _pixelPin = pixelPin;
    _leds = leds;

}

void ConcreteLedBoard::show() {
    FastLED.show();

}

void ConcreteLedBoard::command(LightCommands lightCommand) {
    switch (lightCommand) {
        case LightCommands::LIGHT_ON:
            Serial.println("set Color RED, pixelPin:");
            Serial.println(_pixelPin);
            for (uint8_t i = 0; i < PixelCount; i++) {
                _leds[i] = CRGB::White;
            }
            isOn = true;
            break;
        case LightCommands::LIGHT_OFF:
            Serial.println("set Color BLACK, pixelPin:");
            Serial.println(_pixelPin);
            for (uint8_t i = 0; i < PixelCount; i++) {
                _leds[i] = CRGB::Black;
            }
            isOn = false;
            break;
        default:
            // should not be here
            break;

    }

}

void ConcreteLedBoard::update(unsigned long newTime) {
    if (newTime - _previousTime > 1000.0) {
        _previousTime = newTime;
        if (isOn) {
            command(LightCommands::LIGHT_OFF);
        } else {
            command(LightCommands::LIGHT_ON);
        }

    }

}