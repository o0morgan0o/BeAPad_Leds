
//#define FASTLED_ALLOW_INTERRUPTS 0
//#define FASTLED_INTERRUPT_RETRY_COUNT 1

#include <AppleMidi.h>
#include <WiFiUdp.h>

#include "AccessPoint.h"
#include "Debug_Helper.h"
#include "LedBoard_Store_FastLedStore.h"
#include "FastLedLedBoardsManager.h"
#include "LightStrategy_Factory.h"
#include "MidiKeyDispatcher.h"
#include "CapacitiveTouch_RealDispatcher.h"
#include "Midi_Handler.h"
#include "Debug_Helper_Serial.h"
#include "Debug_Helper_Inactive.h"
#include "RTP_Midi_MidiHandler.h"

APPLEMIDI_CREATE_INSTANCE(WiFiUDP, AppleMIDI, "AppleMIDI-ESP32", DEFAULT_CONTROL_PORT);

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif
#define NUMBER_OF_BOARDS 8
AccessPoint *accessPoint;
//
Debug_Helper *debugHelper;
Debug_Helper *inactiveDebugHelper;
LedBoard_Store_Interface *ledBoardStore;
LedBoardsManager *ledBoardsManager;
LightStrategy_Factory *lightStrategyFactory;
MidiKeyDispatcher *midiKeyDispatcher;
CapacitiveTouch_RealDispatcher *capacitiveTouchDispatcher;
Midi_Handler *midiHandler;
//

void setup() {

    // **************************
    // DEBUG HELPER
    //    debugHelper = new Debug_Helper();
    debugHelper = new Debug_Helper_Serial();
    inactiveDebugHelper = new Debug_Helper_Inactive();



    // **************************
    // CREATION LOF LIGHT STRATEGY FACTORY
    lightStrategyFactory = new LightStrategy_Factory();

    // **************************
    // ADD BOARDS TO STORE
    ledBoardStore = new LedBoard_Store_FastLedStore();
    for (uint8_t i = 0; i < NUMBER_OF_BOARDS; i++) {
        ledBoardStore->addBoard(new FastLedLedBoard(lightStrategyFactory));
    }

    // **************************
    // REINIT LEDS
    FastLED.showColor(CRGB::Black);



    // **************************
    // INITIALIZE BOARD MANAGER
    ledBoardsManager = new FastLedLedBoardsManager(ledBoardStore, lightStrategyFactory);
    ledBoardsManager->init();
    ledBoardsManager->setBoardBaseColor(0, 200, 0, 0);
    ledBoardsManager->setBoardBaseColor(1, CRGB::Orange);
    ledBoardsManager->setBoardBaseColor(2, CRGB::Green);
    ledBoardsManager->setBoardBaseColor(3, CRGB::Blue);
    ledBoardsManager->setBoardBaseColor(4, CRGB::Violet);
    ledBoardsManager->setBoardBaseColor(5, 255, 255, 255);
    ledBoardsManager->setBoardBaseColor(6, CRGB::Yellow);
    ledBoardsManager->setBoardBaseColor(7, CRGB::Pink);
    ledBoardsManager->reinitBoardsLightStrategies();

    // *************************
    // DEFINITIONS OF STRATEGY FOR EACH BOARD
    ledBoardsManager->changeStrategyOnBoard(0, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
    ledBoardsManager->changeStrategyOnBoard(1, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
    ledBoardsManager->changeStrategyOnBoard(2, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
    ledBoardsManager->changeStrategyOnBoard(3, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
    ledBoardsManager->changeStrategyOnBoard(4, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
    ledBoardsManager->changeStrategyOnBoard(5, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
    ledBoardsManager->changeStrategyOnBoard(6, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
    ledBoardsManager->changeStrategyOnBoard(7, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);


    // ***************************
    // DEBUG FUNCTION TO CHECK LIGHT OF BOARD
    //    ledBoardsManager->lightCommandOnBoard(0, LightCommands::LIGHT_ON);
    //    ledBoardsManager->lightCommandOnBoard(1, LightCommands::LIGHT_ON);
    //    ledBoardsManager->lightCommandOnBoard(2, LightCommands::LIGHT_ON);
    //    ledBoardsManager->lightCommandOnBoard(3, LightCommands::LIGHT_ON);
    //    ledBoardsManager->lightCommandOnBoard(4, LightCommands::LIGHT_ON);
    //    ledBoardsManager->lightCommandOnBoard(5, LightCommands::LIGHT_ON);
    //    ledBoardsManager->lightCommandOnBoard(6, LightCommands::LIGHT_ON);
    //    ledBoardsManager->lightCommandOnBoard(7, LightCommands::LIGHT_ON);
    //    ledBoardsManager->setRandomColorForEachBoard();

    // ****************************
    // MIDI KEY DISPATCHER
    midiKeyDispatcher = new MidiKeyDispatcher(ledBoardsManager, inactiveDebugHelper);
    midiKeyDispatcher->connectBoardToMidiKey(0, 60);
    midiKeyDispatcher->connectBoardToMidiKey(1, 61);
    midiKeyDispatcher->connectBoardToMidiKey(2, 62);
    midiKeyDispatcher->connectBoardToMidiKey(3, 63);
    midiKeyDispatcher->connectBoardToMidiKey(4, 64);
    midiKeyDispatcher->connectBoardToMidiKey(5, 65);
    midiKeyDispatcher->connectBoardToMidiKey(6, 66);
    midiKeyDispatcher->connectBoardToMidiKey(7, 67);


    // *************************
    // ACCESS POINT
    accessPoint = new AccessPoint(ledBoardsManager, inactiveDebugHelper);
    accessPoint->init();


    // **************************
    // RTP_MIDI
    midiHandler = new RTP_Midi_MidiHandler(midiKeyDispatcher, debugHelper, &AppleMIDI, &AppleAppleMIDI);
    midiHandler->init();
    //
    AppleMIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
        midiHandler->handleOn(channel, note, velocity);
    });
    AppleMIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
        midiHandler->handleNoteOff(channel, note, velocity);
    });
    AppleAppleMIDI.setHandleConnected([](const APPLEMIDI_NAMESPACE::ssrc_t &ssrc, const char *name) {
        midiHandler->handleConnected();
    });
    AppleAppleMIDI.setHandleDisconnected([](const APPLEMIDI_NAMESPACE::ssrc_t &ssrc) {
        midiHandler->handleDisconnected();
    });

    // **************************
    // TOUCH SENSORS INIT
    capacitiveTouchDispatcher = new CapacitiveTouch_RealDispatcher(midiHandler, debugHelper);
    capacitiveTouchDispatcher->begin();
}


void loop() {

    // Deactivate if webServer Not Needed
    accessPoint->loop();

    // capacitiveTouch loop
    capacitiveTouchDispatcher->loop();

    // check midi Messages
    midiHandler->loop();

    // update and show LedBoardManager
    ledBoardsManager->update(millis());
    if (debugHelper->getDebugFullLight()) {
        ledBoardsManager->showGlobally(CRGB::Red);
    } else {
        ledBoardsManager->show();
    }
}