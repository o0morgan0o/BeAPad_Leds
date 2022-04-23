#include "Board.h"
#include "ConcreteLedBoard.h"
#include "ConcreteLedBoardsManager.h"
#include "ILedBoard.h"
#include "ILedBoardsManager.h"
#include <Arduino.h>
#include "AccessPoint.h"
#include "MyColors.h"
#include "Debug_Helper.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

//#define NO_SESSION_NAME
#define ONE_PARTICIPANT
#include <AppleMidi.h>

#include <ESPmDNS.h>


#define colorSaturation 128
#define NUM_LEDS_PER_STRIP 9
#define NUMBER_OF_BOARDS 8
AccessPoint *accessPoint;
MyColors *myColors;
ILedBoardsManager *ledBoardsManager;
std::vector<ILedBoard *> ledBoards;

Debug_Helper* debugHelper;

APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE();

void setup() {


    // **************************
    // DEBUG HELPER
    debugHelper = new Debug_Helper();

    // **************************
    // SERIAL
    //    Serial.begin(115200);
    //    while (!Serial); // wait for serial attach
    //    Serial.println();
    //    Serial.println("Initializing...");
    //    Serial.flush();



    // **************************
    // INITIALIZE BOARDS
    ledBoards.reserve(NUMBER_OF_BOARDS);
    for (uint8_t i = 0; i < NUMBER_OF_BOARDS; i++) {
        ledBoards.emplace_back(new ConcreteLedBoard());
    }



    // **************************
    // INITIALIZE BOARD MANAGER
    ledBoardsManager = new ConcreteLedBoardsManager(ledBoards);
    ledBoardsManager->init();
    ledBoardsManager->setRandomColorForEachBoard();
    ledBoardsManager->lightAll(60, 60, 60);
    ledBoardsManager->show();
    delay(300);
    ledBoardsManager->forceLightOff();
    ledBoardsManager->show();
    delay(300);

    // *************************
    // ACCESS POINT
    accessPoint = new AccessPoint("gonzyProject", "password", ledBoardsManager, debugHelper);
    accessPoint->init();

    // **************************
    // RTP_MIDI
    if (!MDNS.begin(AppleMIDI.getName()))
            DBG(F("Error setting up MDNS responder!"));
    char str[128] = "";
    strcat(str, AppleMIDI.getName());
    strcat(str, ".local");
    MDNS.addService("apple-midi", "udp", AppleMIDI.getPort());
    MIDI.begin(MIDI_CHANNEL_OMNI);


    AppleMIDI.setHandleConnected([](const APPLEMIDI_NAMESPACE::ssrc_t &ssrc, const char *name) {
        ledBoardsManager->showSuccessSignal();
        //        isConnected++;
        //        DBG(F("Connected to session"), ssrc, name);
    });
    AppleMIDI.setHandleDisconnected([](const APPLEMIDI_NAMESPACE::ssrc_t &ssrc) {
        ledBoardsManager->showErrorSignal();
        //        isConnected--;
        //        DBG(F("Disconnected"), ssrc);
    });
    MIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
        ledBoardsManager->lightAll(120, 120, 120);
        ledBoardsManager->show();
    });
    MIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
        ledBoardsManager->forceLightOff();
        ledBoardsManager->show();
    });

}

void loop() {
    MIDI.read();
    ledBoardsManager->update(millis());
    ledBoardsManager->show();
//    gettimerMi
//    Serial.println("OK...");
//    ledBoardsManager->lightAll();
//    ledBoardsManager->show();
//    delay(500);
//    accessPoint->loop();
//    delay(1000);
//    Serial.println("Colors R, G, B, W...");
//    for (int i = 0; i < PixelCount; i++) {
//        strip.SetPixelColor(i, *myColors->white);
//
//    }
//    strip.Show();
//    delay(1000);
//    Serial.println("Off ...");
//    for (int i = 0; i < PixelCount; i++) {
//        strip.SetPixelColor(i, *myColors->black);
//
//    }
//    strip.Show();
//    delay(1000);

    accessPoint->loop();

}