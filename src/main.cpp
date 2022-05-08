
#include <AppleMidi.h>
#include <WiFiUdp.h>
#include "AccessPoint.h"
#include "Debug_Helper.h"
#include "LightStrategy_Factory.h"
#include "MidiKeyReceiver.h"
#include "CapacitiveTouch_RealDispatcher.h"
#include "Midi_Handler.h"
#include "Debug_Helper_Serial.h"
#include "Debug_Helper_Inactive.h"
#include "RTP_Midi_MidiHandler.h"
#include "DebugHelper_WebSocket.h"
#include "MidiKeySender.h"
#include <Wire.h>
#include "LedBoard_Store_NeoPixelStore.h"
#include "NeoPixelBoard.h"
#include "NeoPixelBoardsManager.h"
#include "CapacitiveTouch_MPR121Dispatcher.h"

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
MidiKeyReceiver *midiReceiver;
MidiKeySender *midiSender;
CapacitiveTouch_Dispatcher *capacitiveTouchDispatcher;
Midi_Handler *midiHandler;
//
//
uint8_t LED_CONTROLLER_ADDRESS{6};
//TwoWire i2cWire = TwoWire(0);

void setup() {
    // ***********************
    // MPR 121

    // **************************
    // DEBUG HELPER
    //    debugHelper = new Debug_Helper();
    debugHelper = new Debug_Helper_Serial();
    inactiveDebugHelper = new Debug_Helper_Inactive();
    //    debugHelper = new Debug_Helper_Inactive();
    //    debugHelper = new DebugHelper_WebSocket();


    // *************************
    // ACCESS POINT
    accessPoint = new AccessPoint();


    // **************************
    // CREATION LOF LIGHT STRATEGY FACTORY
    lightStrategyFactory = new LightStrategy_Factory();

    // **************************
    // ADD BOARDS TO STORE
    ledBoardStore = new LedBoard_Store_NeoPixelStore();
    ledBoardStore->addBoard(new NeoPixelBoard(32, 9, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(33, 9, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(25, 9, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(26, 9, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(27, 9, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(14, 9, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(12, 9, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(13, 9, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(23, 9, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(18, 9, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(5, 9, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(17, 9, lightStrategyFactory));

    // **************************
    // INITIALIZE BOARD MANAGER
    ledBoardsManager = new NeoPixelBoardsManager(ledBoardStore, lightStrategyFactory);
    ledBoardsManager->init();
    ledBoardsManager->setBoardBaseColor(0, 255, 0, 255);
    ledBoardsManager->setBoardBaseColor(1, 0, 200, 0);
    ledBoardsManager->setBoardBaseColor(2, CRGB::Orange);
    ledBoardsManager->setBoardBaseColor(3, CRGB::Green);
    ledBoardsManager->setBoardBaseColor(4, CRGB::Blue);
    ledBoardsManager->setBoardBaseColor(5, 255, 255, 255);
    ledBoardsManager->setBoardBaseColor(6, CRGB::Yellow);
    ledBoardsManager->setBoardBaseColor(7, CRGB::Pink);
    //
    ledBoardsManager->showBaseColor();
//    ledBoardsManager->reinitBoardsLightStrategies();

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
//        ledBoardsManager->lightCommandOnBoard(0, LightCommands::LIGHT_ON);
//        ledBoardsManager->lightCommandOnBoard(1, LightCommands::LIGHT_ON);
//        ledBoardsManager->lightCommandOnBoard(2, LightCommands::LIGHT_ON);
//        ledBoardsManager->lightCommandOnBoard(3, LightCommands::LIGHT_ON);
//        ledBoardsManager->lightCommandOnBoard(4, LightCommands::LIGHT_ON);
//        ledBoardsManager->lightCommandOnBoard(5, LightCommands::LIGHT_ON);
//        ledBoardsManager->lightCommandOnBoard(6, LightCommands::LIGHT_ON);
//        ledBoardsManager->lightCommandOnBoard(7, LightCommands::LIGHT_ON);
    //    ledBoardsManager->setRandomColorForEachBoard();

    // ****************************
    // MIDI KEY RECEIVER
    midiReceiver = new MidiKeyReceiver(ledBoardsManager, inactiveDebugHelper);
    midiReceiver->connectBoardToReceiveMidiKey(0, 60);
    midiReceiver->connectBoardToReceiveMidiKey(1, 61);
    midiReceiver->connectBoardToReceiveMidiKey(2, 62);
    midiReceiver->connectBoardToReceiveMidiKey(3, 63);
    midiReceiver->connectBoardToReceiveMidiKey(4, 64);
    midiReceiver->connectBoardToReceiveMidiKey(5, 65);
    midiReceiver->connectBoardToReceiveMidiKey(6, 66);
    midiReceiver->connectBoardToReceiveMidiKey(7, 67);

    // ***************************
    // MIDI KEY SENDER
    midiSender = new MidiKeySender(ledBoardsManager, debugHelper);
    midiSender->connectBoardToSendMidiKey(0,0, 60);
    midiSender->connectBoardToSendMidiKey(1,0, 61);
    midiSender->connectBoardToSendMidiKey(2,0, 62);
    midiSender->connectBoardToSendMidiKey(3,0, 63);
    midiSender->connectBoardToSendMidiKey(4,2, 64);
    midiSender->connectBoardToSendMidiKey(5,0, 65);
    midiSender->connectBoardToSendMidiKey(6,0, 66);
    midiSender->connectBoardToSendMidiKey(7,0, 67);


    // **************************
    // RTP_MIDI
    midiHandler = new RTP_Midi_MidiHandler(midiReceiver, midiSender, debugHelper, &AppleMIDI, &AppleAppleMIDI);
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
    capacitiveTouchDispatcher = new CapacitiveTouch_MPR121Dispatcher(ledBoardsManager, midiHandler, debugHelper);
    capacitiveTouchDispatcher->begin();

    // ***************************
    // ACCESS POINT SERVER INIT
    accessPoint->init(ledBoardsManager, debugHelper);

}

void loop() {

    // Deactivate if webServer Not Needed
    accessPoint->loop();

    // check midi Messages
    midiHandler->loop();

    // capacitiveTouch loop
    capacitiveTouchDispatcher->loop();

    // update and show LedBoardManager
    ledBoardsManager->update(millis());
    ledBoardsManager->show();

//    if (debugHelper->getDebugFullLight()) {
//        ledBoardsManager->showGlobally(CRGB::Red);
//    } else {
//        ledBoardsManager->show();
//    }
//    ledBoardsManager->showBaseColor();

}