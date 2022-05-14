//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_ILEDBOARD_H
#define GONZYPROJECT_ILEDBOARD_H

#include <cstdint>

#ifdef IN_TESTING
#include "../test/Fake_CRGB.h"
#else
#include <FastLED.h>
#endif

#include "LightCommands.h"
#include "LightStrategy.h"
#include "FullLightStrategy.h"
#include "NoLightStrategy.h"
#include "RGB_Color.h"
#include "LightStrategy_Factory.h"
#include "StrategyMixer.h"

class LedBoardsManager;

class LedBoard {
public:
    explicit LedBoard(uint8_t nb_pixels, LightStrategy_Factory *lightStrategyFactory);

    virtual void giveReferenceManager(LedBoardsManager *manager);

    virtual LedBoardsManager *getManager();

    virtual void changeLightStrategy(LIGHT_STRATEGIES newStrategy);

    virtual void reinitLightStrategy();

    virtual void showBaseColor() = 0;

    /**
     * This should be used only for display high-priority messages (like error messages)
     * @param color
     */
    virtual void showGlobalColor(CRGB color) = 0;

    virtual void show() = 0;;

    virtual void triggerOn();

    virtual void triggerOn(LIGHT_STRATEGIES strategy);

    virtual void triggerOff();

    virtual void updateLedColorInBoard(uint8_t ledIndexInBoard, CRGB updatedColor) = 0;

    virtual void updateLedColorInBoard(uint8_t ledIndexInBoard, uint8_t r, uint8_t g, uint8_t b) = 0;

    virtual void updateValues(unsigned long newTime);;

    virtual void setBoardColor(uint8_t r, uint8_t g, uint8_t b);;

    virtual void setBoardColor(CRGB color);;

    virtual unsigned long getCurrentTime();

    virtual CRGB *getBoardLeds();

    virtual RGB_Color getBoardBaseColor();

    virtual void initBoard() =0;


    virtual void mixStrategies();

    uint8_t NUM_PIXELS;
public:
    CRGB *_leds{};
    RGB_Color _boardBaseColor{255, 255, 0};
    unsigned long _currentTime{0};
protected:
    LightStrategy_Factory *_lightStrategyFactory;
    LightStrategy *_midiReceiveLightStrategy;
//    LightStrategy *_touchSensorLightStrategy;
    LightStrategy *_shiftLightStrategy;
protected:
    LedBoardsManager *_manager{};

};

#endif //GONZYPROJECT_ILEDBOARD_H