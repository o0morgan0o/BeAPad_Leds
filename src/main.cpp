#include "Board.h"
#include "ConcreteLedBoard.h"
#include "ConcreteLedBoardsManager.h"
#include "ILedBoard.h"
#include "ILedBoardsManager.h"
#include <Arduino.h>
#include "AccessPoint.h"
#include "MyColors.h"


#define colorSaturation 128
#define NUM_LEDS_PER_STRIP 9
#define NUMBER_OF_BOARDS 8

AccessPoint *accessPoint;
MyColors *myColors;
ILedBoardsManager* ledBoardsManager;
std::vector<ILedBoard*> ledBoards;


void setup() {

    // **************************
    // SERIAL
    Serial.begin(115200);
    while (!Serial); // wait for serial attach
    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();

    // **************************
    // INITIALIZE BOARDS
    ledBoards.reserve(NUMBER_OF_BOARDS);
    for(uint8_t i=0; i< NUMBER_OF_BOARDS; i++){
        ledBoards.emplace_back(new ConcreteLedBoard());
    }



    // **************************
    // INITIALIZE BOARD MANAGER
    ledBoardsManager = new ConcreteLedBoardsManager(ledBoards);
    ledBoardsManager->init();
    ledBoardsManager->setRandomColorForEachBoard();
    ledBoardsManager->lightAll();
    ledBoardsManager->show();

    // init colors
//    myColors = new MyColors();

    // *************************
    // ACCESS POINT
    accessPoint = new AccessPoint("gonzyProject", "password");
    accessPoint->init();

}

void loop() {
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

}