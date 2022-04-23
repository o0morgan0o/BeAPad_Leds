#include "AccessPoint.h"

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

AccessPoint::AccessPoint(char *ssid, char *password, ILedBoardsManager *manager) {
    _ssid = ssid;
    _password = password;
    _manager = manager;
}

void AccessPoint::init() {
    WiFi.softAP(_ssid, _password);
    // Print local IP address and start web server
//    Serial.println("");
//    Serial.println("WiFi started.");
//    Serial.println("IP address: ");
//    Serial.println(WiFi.softAPIP());
//    server.begin();

    server.on("/", HTTP_GET, [=](AsyncWebServerRequest *request) {
        request->send(200, "text/html", homePage);
    });
    server.on("/L", HTTP_GET, [=](AsyncWebServerRequest *request) {
        request->send(200, "text/html", homePage);
        _manager->forceLightOff();
    });
    server.on("/light", HTTP_POST, [=](AsyncWebServerRequest *request) {
        if (request->hasParam("r", true)) {
            auto r = request->getParam("r", true)->value().toInt();
            auto g = request->getParam("g", true)->value().toInt();
            auto b = request->getParam("b", true)->value().toInt();
            _manager->lightAll(r,g,b);
            String responseString = "Done";
            responseString+= "param R";
            responseString += r;
            request->send(200, "text/plain", responseString);
        }
    });
    server.onNotFound(notFound);
    server.begin();
}

void AccessPoint::loop() {
}