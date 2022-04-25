//#include "LedBoard.h"
//#include "LedBoardsManager.h"
//#include <Arduino.h>
//#include "AccessPoint.h"
//#include "MyColors.h"
#include "Debug_Helper.h"
#include "LedBoard_Store_FastLedStore.h"
#include "FastLedLedBoardsManager.h"

//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WiFiUdp.h>
//
////#define NO_SESSION_NAME
//#define ONE_PARTICIPANT
//#include <AppleMidi.h>
//
//#include <ESPmDNS.h>
//
//
//#define colorSaturation 128
//#define NUM_LEDS_PER_STRIP 9
#define NUMBER_OF_BOARDS 8
//
//AccessPoint *accessPoint;
//MyColors *myColors;
//

Debug_Helper *debugHelper;
LedBoard_Store_Interface *ledBoardStore;
LedBoardsManager *ledBoardsManager;
//
//APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE();

void setup() {


    // **************************
    // DEBUG HELPER
    debugHelper = new Debug_Helper();


    // **************************
    // ADD BOARDS TO STORE
    ledBoardStore = new LedBoard_Store_FastLedStore();
    for (uint8_t i = 0; i < NUMBER_OF_BOARDS; i++) {
        ledBoardStore->addBoard(new FastLedLedBoard());
    }



    // **************************
    // INITIALIZE BOARD MANAGER
    ledBoardsManager = new FastLedLedBoardsManager(ledBoardStore);
    ledBoardsManager->init();
    ledBoardsManager->setBoardBaseColor(0, 200, 0, 0);
    ledBoardsManager->setBoardBaseColor(1, CRGB::Orange);
    ledBoardsManager->setBoardBaseColor(2, CRGB::Green);
    ledBoardsManager->setBoardBaseColor(3, CRGB::Blue);
    ledBoardsManager->setBoardBaseColor(4, CRGB::Violet);
    ledBoardsManager->setBoardBaseColor(5, 255,255,255);
    ledBoardsManager->setBoardBaseColor(6, CRGB::Yellow);
    ledBoardsManager->setBoardBaseColor(7, CRGB::Pink);


//    ledBoardsManager->setStrategy(0, )

//    ledBoardsManager->showGlobally(CRGB{0, 0, 120});
    ledBoardsManager->lightCommandOnBoard(0, LightCommands::LIGHT_ON);
//    ledBoardsManager->lightCommandOnBoard(1, LightCommands::LIGHT_ON);
//    ledBoardsManager->lightCommandOnBoard(2, LightCommands::LIGHT_ON);
//    ledBoardsManager->lightCommandOnBoard(3, LightCommands::LIGHT_ON);
//    ledBoardsManager->lightCommandOnBoard(4, LightCommands::LIGHT_ON);
//    ledBoardsManager->lightCommandOnBoard(5, LightCommands::LIGHT_ON);
//    ledBoardsManager->lightCommandOnBoard(6, LightCommands::LIGHT_ON);
//    ledBoardsManager->lightCommandOnBoard(7, LightCommands::LIGHT_ON);


//    ledBoardsManager->setRandomColorForEachBoard();
//
//    // *************************
//    // ACCESS POINT
//    accessPoint = new AccessPoint("gonzyProject", "password", ledBoardsManager, debugHelper);
//    accessPoint->giveReferenceManager();
//
//    // **************************
//    // RTP_MIDI
//    if (!MDNS.begin(AppleMIDI.getName()))
//            DBG(F("Error setting up MDNS responder!"));
//    char str[128] = "";
//    strcat(str, AppleMIDI.getName());
//    strcat(str, ".local");
//    MDNS.addService("apple-midi", "udp", AppleMIDI.getPort());
//    MIDI.begin(MIDI_CHANNEL_OMNI);
//
//
//    AppleMIDI.setHandleConnected([](const APPLEMIDI_NAMESPACE::ssrc_t &ssrc, const char *name) {
//        ledBoardsManager->showSuccessSignal();
//        //        isConnected++;
//        //        DBG(F("Connected to session"), ssrc, name);
//    });
//    AppleMIDI.setHandleDisconnected([](const APPLEMIDI_NAMESPACE::ssrc_t &ssrc) {
//        ledBoardsManager->showErrorSignal();
//        //        isConnected--;
//        //        DBG(F("Disconnected"), ssrc);
//    });
//    MIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
//        ledBoardsManager->lightAll(120, 120, 120);
//        ledBoardsManager->show();
//    });
//    MIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
//        ledBoardsManager->forceLightOff();
//        ledBoardsManager->show();
//    });

}

void loop() {
//    MIDI.read();
    ledBoardsManager->update(millis());
    ledBoardsManager->show();
//    accessPoint->loop();

}