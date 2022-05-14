
#include <AppleMidi.h>
#include <WiFiUdp.h>
#include "AccessPoint.h"
#include "Debug_Helper.h"
#include "LightStrategy_Factory.h"
#include "MidiKeyReceiver.h"
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
#include "CapacitiveTouch_Dispatcher.h"
#include "Capacitive_Sensor.h"
#include "MPR121_Sensor.h"
#include "main_constants.h"

#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_0 2
#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_1 1
#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_2 0
#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_3 3
#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_4 4
#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_5 5
#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_6 6
#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_7 7
#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_8 8
#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_9 11
#define MPR_TOUCH_PIN_CONNECTED_TO_BOARD_10 10
APPLEMIDI_CREATE_INSTANCE(WiFiUDP, AppleMIDI, "AppleMIDI-ESP32", DEFAULT_CONTROL_PORT);
AccessPoint *accessPoint;
//
Debug_Helper *debugHelper;
Debug_Helper *inactiveDebugHelper;
LedBoard_Store_Interface *ledBoardStore;
LedBoardsManager *ledBoardsManager;
LightStrategy_Factory *lightStrategyFactory;
MidiKeyReceiver *midiReceiver;
MidiKeySender *midiSender;
ICapacitiveTouch_Dispatcher *capacitiveTouchDispatcher;
Midi_Handler *midiHandler;
Capacitive_Sensor *touchSensor;

void setup() {

    // **************************
    // DEBUG HELPER
    //    debugHelper = new Debug_Helper();
    //    debugHelper = new Debug_Helper_Inactive();
    //    debugHelper = new DebugHelper_WebSocket();
    debugHelper = new Debug_Helper_Serial();
    inactiveDebugHelper = new Debug_Helper_Inactive();

    // *************************
    // ACCESS POINT
    accessPoint = new AccessPoint();

    // **************************
    // CREATION LOF LIGHT STRATEGY FACTORY
    lightStrategyFactory = new LightStrategy_Factory();

    // **************************
    // ADD BOARDS TO STORE
    // NeoPixelBoard 1st param = GPIO Pin
    ledBoardStore = new LedBoard_Store_NeoPixelStore();
    uint8_t NUM_PIXELS_PER_BOARD = 9;
    // NOTE : VERY IMPORTANT TO KEEP THE SAME ORDER OF THE PCB
    ledBoardStore->addBoard(new NeoPixelBoard(32, NUM_PIXELS_PER_BOARD, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(33, NUM_PIXELS_PER_BOARD, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(25, NUM_PIXELS_PER_BOARD, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(23, NUM_PIXELS_PER_BOARD, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(3, NUM_PIXELS_PER_BOARD, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(19, NUM_PIXELS_PER_BOARD, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(4, NUM_PIXELS_PER_BOARD, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(26, NUM_PIXELS_PER_BOARD, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(27, NUM_PIXELS_PER_BOARD, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(14, NUM_PIXELS_PER_BOARD, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(12, NUM_PIXELS_PER_BOARD, lightStrategyFactory));
    ledBoardStore->addBoard(new NeoPixelBoard(13, NUM_PIXELS_PER_BOARD, lightStrategyFactory));

    // **************************
    // DEFINE PALETTE

    // **************************
    // INITIALIZE BOARD MANAGER
    ledBoardsManager = new NeoPixelBoardsManager(ledBoardStore, lightStrategyFactory, debugHelper);
    ledBoardsManager->init();
    ledBoardsManager->setBoardBaseColor(0, CRGB::Amethyst);
    ledBoardsManager->setBoardBaseColor(1, CRGB::Amethyst);
    ledBoardsManager->setBoardBaseColor(2, CRGB::Aquamarine);
    ledBoardsManager->setBoardBaseColor(3, CRGB::Aquamarine);
    ledBoardsManager->setBoardBaseColor(4, CRGB::Brown);
    ledBoardsManager->setBoardBaseColor(5, CRGB::Brown);
    ledBoardsManager->setBoardBaseColor(6, CRGB::Chocolate);
    ledBoardsManager->setBoardBaseColor(7, CRGB::Chocolate);
    ledBoardsManager->setBoardBaseColor(8, CRGB::Yellow);
    ledBoardsManager->setBoardBaseColor(9, CRGB::Yellow);
    ledBoardsManager->setBoardBaseColor(10, CRGB::Yellow);
    ledBoardsManager->setBoardBaseColor(11, CRGB::Yellow);
    // Shift color
    ledBoardsManager->setShiftColor(CRGB::Blue);
    //
//    ledBoardsManager->showBaseColor();
    ledBoardsManager->giveAllBoardsReferenceOfManager();

    // *************************
    // DEFINITIONS OF STRATEGY FOR EACH BOARD
    // TODO be sure that when a user trigger a board this is this strategy which is used
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(0, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(1, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(2, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(3, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(4, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(5, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(6, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(7, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(8, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(9, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(10, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setTriggerOnTouchLightStrategyOnBoard(11, LIGHT_STRATEGIES::STRATEGY_SHIFT_KEY_STRATEGY);
//    ledBoardsManager->setLightStrategyForChannel(1, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    ledBoardsManager->setLightStrategyForChannel(2, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);

    // ****************************
    // MIDI KEY RECEIVER
    // explanations: connectBoardToReceiveMidiKey(60, 0);
    // it means when MidiNote 60 is received a triggerOnSignalIsSendOn board 0
    // TODO Try to handle things differently so that we can send a midi Message to multiple boards
    midiReceiver = new MidiKeyReceiver(ledBoardsManager, inactiveDebugHelper);
//    midiReceiver->connectBoardToReceiveMidiKey(0, 60, LIGHT_STRATEGIES::STRATEGY_FADE_IN_AND_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(1, 61, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(2, 62, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(3, 63, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(4, 64, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(5, 65, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(6, 66, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(7, 67, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(8, 68, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(9, 69, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
//    midiReceiver->connectBoardToReceiveMidiKey(10, 70, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);

    // ***************************
    // MIDI KEY SENDER
    // explanations : connectBoardToSendMidiKey(1, 4 ,87)
    // it means that touchPin1 (in MPR121) is connected to board 4
    // ,and it will send midiNote 87 when touched
    // NOTE:
    // Last board (11 from index 0) is not connected to midiSend or touchPin because it acts as a shift button
    midiSender = new MidiKeySender(ledBoardsManager, debugHelper);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_0, 0, 60, 80);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_1, 1, 61, 81);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_2, 2, 62, 82);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_3, 3, 63, 83);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_4, 4, 64, 84);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_5, 5, 65, 85);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_6, 6, 66, 86);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_7, 7, 67, 87);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_8, 8, 68, 88);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_9, 9, 69, 89);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_10, 10, 70, 90);
    midiSender->connectBoardToSendMidiKey(MPR_TOUCH_PIN_CONNECTED_TO_BOARD_11_SHIFT_PIN, 11, NO_MIDI_TRIGGER_FOR_BOARD, NO_MIDI_TRIGGER_FOR_BOARD);

    // **************************
    // RTP_MIDI
    midiHandler = new RTP_Midi_MidiHandler(midiReceiver, midiSender, debugHelper, &AppleMIDI, &AppleAppleMIDI);
    midiHandler->init();
    // set eventListeners
    // TODO implements MIDI_CC change (maybe for controlling the colors)
    AppleMIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
        midiHandler->handleOn(channel, note, velocity);
    });
    AppleMIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
        midiHandler->handleNoteOff(channel, note, velocity);
    });
    AppleAppleMIDI.setHandleConnected([](const APPLEMIDI_NAMESPACE::ssrc_t &ssrc, const char *name) {
        ledBoardsManager->showBlinkHighPriorityMessage(BlinkHighPriorityMessages::RTP_CONNECTION_SUCCESS);
        midiHandler->handleConnected();
    });
    AppleAppleMIDI.setHandleDisconnected([](const APPLEMIDI_NAMESPACE::ssrc_t &ssrc) {
        ledBoardsManager->showBlinkHighPriorityMessage(BlinkHighPriorityMessages::RTP_CONNECTION_LOST);
        midiHandler->handleDisconnected();
    });

    // **************************
    // TOUCH SENSORS INIT (MPR121)
    touchSensor = new MPR121_Sensor();
    capacitiveTouchDispatcher = new CapacitiveTouch_Dispatcher(ledBoardsManager, midiHandler, debugHelper, touchSensor);
    capacitiveTouchDispatcher->begin();
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(0, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(1, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(2, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(3, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(4, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(5, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(6, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(7, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(8, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(9, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(10, LIGHT_STRATEGIES::STRATEGY_FADE_OUT);
    capacitiveTouchDispatcher->setTriggerOnTouchLightStrategyOnBoard(11, LIGHT_STRATEGIES::STRATEGY_SHIFT_KEY_STRATEGY);

    // ***************************
    // ACCESS POINT SERVER INIT
    accessPoint->init(ledBoardsManager, inactiveDebugHelper);

    // *************************
    // FINALIZE INITIALISATION
//    ledBoardsManager->reinitBoardsLightStrategies();
//    ledBoardsManager->showBlinkHighPriorityMessage(BlinkHighPriorityMessages::SHOW_END_OF_SETUP_MESSAGE);

}

void loop() {

    // can be deactivated if webServer Not Needed
    accessPoint->loop();

//    // check midi Messages
//    midiHandler->loop();
//
//    // capacitiveTouch loop
//    capacitiveTouchDispatcher->loop();
//
//    // updateValues and show LedBoardManager
//    ledBoardsManager->update(millis());
//    ledBoardsManager->show();

}