#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include <WiFi.h>
#include <WiFiClient.h>
#include "ILedBoardsManager.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


struct AccessPoint {
public:
    AccessPoint(char *ssid, char *password, ILedBoardsManager *manager);

    void init();

    void loop();

private:
    // set server port number to 80
//    WiFiServer server{80};
    ILedBoardsManager *_manager;
    char *_ssid;
    char *_password;
    AsyncWebServer server{80};
//    char* homePage= "<h1>hello</h1>";

    String homePage =
            "<h1>BaAPad</h1><br/>"
            "<form action='/light' method='POST'><input type='submit' value='LIGHT'/>"
            "<h2>r</h2><input type='range' id='r' name='r' min='0' max='127' step='1' value='50' /><br/>"
            "<h2>g</h2><input type='range' id='g' name='g' min='0' max='127' step='1' value='50' /><br/>"
            "<h2>b</h2><input type='range' id='b' name='b' min='0' max='127' step='1' value='50'  /><br/><br/>"
            "<input id='validation' name='validate' value='VALIDATE'  style='display:none;'/>"
            "</form>"
            "<a href='L'>here to turn OFF the LED.</a><br>";

};

#endif