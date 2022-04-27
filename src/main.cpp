//#include <Arduino.h>
#include "AccessPoint.h"
#include "Debug_Helper.h"
#include "LedBoard_Store_FastLedStore.h"
#include "FastLedLedBoardsManager.h"
#include "LightStrategy_Factory.h"
#include "MidiKeyDispatcher.h"

#define ONE_PARTICIPANT

#include <AppleMidi.h>
#include <ESPmDNS.h>

#define NUMBER_OF_BOARDS 8

AccessPoint *accessPoint;
//MyColors *myColors;

Debug_Helper *debugHelper;
LedBoard_Store_Interface *ledBoardStore;
LedBoardsManager *ledBoardsManager;
LightStrategy_Factory *lightStrategyFactory;
MidiKeyDispatcher *midiKeyDispatcher;
//
APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE();

void setup() {

    // **************************
    // DEBUG HELPER
    debugHelper = new Debug_Helper();

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
    midiKeyDispatcher = new MidiKeyDispatcher(ledBoardsManager, debugHelper);
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
    accessPoint = new AccessPoint(ledBoardsManager, debugHelper);
    accessPoint->init();

    // **************************
    // RTP_MIDI
    if (!MDNS.begin(AppleMIDI.getName()))
        debugHelper->add("Error setting up MDNS responded !");
    debugHelper->logRTPMidiInit(AppleMIDI.getName(), String{AppleMIDI.getPort()});
    MDNS.addService("apple-midi", "udp", AppleMIDI.getPort());
    MIDI.begin(MIDI_CHANNEL_OMNI);
    //
    AppleMIDI.setHandleConnected([](const APPLEMIDI_NAMESPACE::ssrc_t &ssrc, const char *name) {
        debugHelper->add("RTP_MIDI Connected !");
    });
    AppleMIDI.setHandleDisconnected([](const APPLEMIDI_NAMESPACE::ssrc_t &ssrc) {
        debugHelper->add("ERROR !!! RTP_MIDI DisConnected !");
    });
    MIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
        debugHelper->logMidiMessage("NOTE_ON", channel, note, velocity);
        midiKeyDispatcher->handleNoteOn(note);
    });
    MIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
        debugHelper->logMidiMessage("NOTE_OFF", channel, note, velocity);
        midiKeyDispatcher->handleNoteOff(note);
    });

}

void loop() {
    MIDI.read();
    ledBoardsManager->update(millis());
    if (debugHelper->getDebugFullLight()) {
        ledBoardsManager->showGlobally(CRGB::Red);
    } else {
        ledBoardsManager->show();
    }

    // Deactivate if webServer Not Needed
    accessPoint->loop();

}