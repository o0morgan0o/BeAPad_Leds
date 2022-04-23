#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include <WiFi.h>
#include <WiFiClient.h>
#include "ILedBoardsManager.h"
#include "Debug_Helper.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

struct AccessPoint {
public:
    AccessPoint(char *ssid, char *password, ILedBoardsManager *manager, Debug_Helper *debugHelper);

    void init();

    void loop();

    String getHomepage() {
        String page = "<div>";
        page += Debug_Helper::getString().c_str();
        page += homePage;
        page += "</div>";
        return page;
    }

private:
    // DEBUG HELPER
    Debug_Helper *_debugHelper;

    // set server port number to 80
//    WiFiServer server{80};
    ILedBoardsManager *_manager;
    char *_ssid;
    char *_password;
    AsyncWebServer server{80};

    String homePage =
            "<h1>BaAPad</h1><br/>"
            "<form action='/light' method='POST'><input type='submit' value='LIGHT'/>"
            "<h2>r</h2><input type='range' id='r' name='r' min='0' max='126' step='1' value='50' /><br/>"
            "<h2>g</h2><input type='range' id='g' name='g' min='0' max='126' step='1' value='50' /><br/>"
            "<h2>b</h2><input type='range' id='b' name='b' min='0' max='126' step='1' value='50'  /><br/><br/>"
            "</form>"
            "<a href='/alloff'>TURN OFF</a><br>"
            "<a href='/allwhite'>TURN WHITE</a><br>";

};

#endif