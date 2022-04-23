//
// Created by morgan on 4/21/2022.
//

#include "ConcreteLedBoard.h"
#include "ILedBoardsManager.h"

ConcreteLedBoard::ConcreteLedBoard() : ILedBoard() {

}

void ConcreteLedBoard::init(CRGB *leds, uint8_t pixelPin, ILedBoardsManager *manager) {
    _manager = manager;
    _pixelPin = pixelPin;
    _leds = leds;

}

void ConcreteLedBoard::show() {
    FastLED.show();

}

void ConcreteLedBoard::command(LightCommands lightCommand) {
    switch (lightCommand) {
        case LightCommands::LIGHT_ON: {
//            Serial.println("set Color RED, pixelPin:");
//            Serial.println(_pixelPin);
            auto newBoardColor = _manager->getCurrentGlobalColor();
            setBoardColor(newBoardColor);
            for (uint8_t i = 0; i < PixelCount; i++) {
//                _leds[i] = _boardColor;
//                _leds[i] = CRGB{0, 120, 0};
                _leds[i] = _boardColor;
                isOn = true;
            }
            break;
        }
        case LightCommands::LIGHT_OFF: {
//            Serial.println("set Color BLACK, pixelPin:");
//            Serial.println(_pixelPin);
            for (uint8_t i = 0; i < PixelCount; i++) {
                _leds[i] = CRGB::Black;
            }
            isOn = false;
            break;
        }
        case LightCommands::LIGHT_SUCCESS: {
            for (uint8_t i = 0; i < PixelCount; i++) {
                _leds[i] = CRGB::Green;
            }
            break;
        }
        case LightCommands::LIGHT_ERROR: {
            for (uint8_t i = 0; i < PixelCount; i++) {
                _leds[i] = CRGB::Red;
            }
            break;
        }
        case LightCommands::LIGHT_WHITE: {
            for (uint8_t i = 0; i < PixelCount; i++) {
                _leds[i] = CRGB::White;
            }
            break;
        }
        default:
            // should not be here
            break;

    }

}

void ConcreteLedBoard::update(unsigned long newTime) {
//    if (newTime - _previousTime > 1000.0) {
//        _previousTime = newTime;
//        if (isOn) {
//            command(LightCommands::LIGHT_OFF);
//        } else {
//            command(LightCommands::LIGHT_ON);
//        }
//
//    }

}

void ConcreteLedBoard::setBoardColor(CRGB color) {
    _boardColor = color;

}