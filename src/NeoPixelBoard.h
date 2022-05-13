//
// Created by morgan on 5/8/2022.
//

#ifndef PLATFORMIO_PROGRAM_NEOPIXELBOARD_H
#define PLATFORMIO_PROGRAM_NEOPIXELBOARD_H

#include "LedBoard.h"
#include "Adafruit_NeoPixel.h"

class NeoPixelBoard : public LedBoard {
public:
    NeoPixelBoard(uint8_t pin, uint8_t nb_pixels, LightStrategy_Factory *lightStrategyFactory) :
            LedBoard(nb_pixels, lightStrategyFactory) {
        _strip = new Adafruit_NeoPixel{nb_pixels, pin, NEO_GRB + NEO_KHZ800};

    }

    void showBaseColor() override {
        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            _strip->setPixelColor(i, _boardBaseColor.r, _boardBaseColor.g, _boardBaseColor.b);
        }
    }

    void showGlobalColor(CRGB color) override {
        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            _strip->setPixelColor(i, color.r, color.g, color.b);
        }
        show();
    }

    void updateLedColorInBoard(uint8_t ledIndexInBoard, CRGB updatedColor) override {
        _strip->setPixelColor(ledIndexInBoard, updatedColor.r, updatedColor.g, updatedColor.b);
    }

    void updateLedColorInBoard(uint8_t ledIndexInBoard, uint8_t r, uint8_t g, uint8_t b) override {
        _strip->setPixelColor(ledIndexInBoard, r, g, b);

    }

    void initBoard() override {
        _strip->begin();
    }

    void show() override {
        _strip->show();
    }

    Adafruit_NeoPixel *_strip;
};

#endif //PLATFORMIO_PROGRAM_NEOPIXELBOARD_H