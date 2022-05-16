#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include <WiFi.h>
#include <WiFiClient.h>
#include "LedBoardsManager.h"
#include "Debug_Helper.h"
#include <WebServer.h>



struct AccessPoint {
public:
    AccessPoint();

    void init(LedBoardsManager *manager, Debug_Helper *debugHelper);

    void loop();

    String getHomepage() {
        String page = "<!DOCTYPE>\r\n<html>\r\n<div>";
        page += _debugHelper->getString().c_str();
        page += homePage;
        page += "</div>\r\n</html>";
        return page;
    }

private:
    Debug_Helper *_debugHelper{};
    LedBoardsManager *_manager{};
    const char *_ssid = "gonzyProject";
    const char *_password = "password";

    // set server port number to 80
    WebServer server{80};

    String homePage =
            "<h1>BeAPad</h1><br/>"
            "<form action='/light' method='POST'><input type='submit' value='LIGHT'/>"
            "<h2>r</h2><input type='range' id='r' name='r' min='0' max='126' step='1' value='50' /><br/>"
            "<h2>g</h2><input type='range' id='g' name='g' min='0' max='126' step='1' value='50' /><br/>"
            "<h2>b</h2><input type='range' id='b' name='b' min='0' max='126' step='1' value='50'  /><br/><br/>"
            "</form>"
            "<a href='/debug_on'>DEBUG ON</a><br>"
            "<a href='/debug_off'>DEBUG OFF</a><br>"
            "<a href='/allwhite'>TURN WHITE</a><br>"
            "<a href='/alloff'>TURN OFF</a><br>";

};

#endif