#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include <WiFi.h>
#include <WiFiClient.h>

struct AccessPoint {
public:
    AccessPoint(char *ssid, char *password) ;

    void init();

    void loop();

private:
    // set server port number to 80
    WiFiServer server{80};
    char *_ssid;
    char *_password;
};
#endif