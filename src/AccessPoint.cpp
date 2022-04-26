#include "AccessPoint.h"

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

AccessPoint::AccessPoint(LedBoardsManager *manager, Debug_Helper *debugHelper) {
    _debugHelper = debugHelper;
    _manager = manager;

}

void AccessPoint::init() {
    WiFiClass::mode(WIFI_AP);
    WiFi.softAP(_ssid, _password);
    // Print local IP address and start web server
    //    Serial.println("");
    //    Serial.println("WiFi started.");
    //    Serial.println("IP address: ");
    //    Serial.println(WiFi.softAPIP());
    server.begin();


//    server.on("/alloff", HTTP_GET, [=](AsyncWebServerRequest *request) {
//        request->send(200, "text/html", getHomepage());
//        _manager->forceLightOff();
//    });

//    server.on("/allwhite", HTTP_GET, [=](AsyncWebServerRequest *request) {
//        request->send(200, "text/html", getHomepage());
//        _manager->lightAll(120,120,120);
//    });

//    server.on("/light", HTTP_POST, [=](AsyncWebServerRequest *request) {
//        if (request->hasParam("r", true)) {
//            auto r = request->getParam("r", true)->value().toInt();
//            auto g = request->getParam("g", true)->value().toInt();
//            auto b = request->getParam("b", true)->value().toInt();
//            _manager->lightAll(r, g, b);
//            String responseString = "LightOn Parameters RGB : ";
//            responseString += r;
//            responseString += g;
//            responseString += b;
//            _debugHelper->add(responseString);
//            request->send(204);
//        }
//    });

    server.on("/trigger", HTTP_POST, [=](AsyncWebServerRequest *request) {
        if (request->hasParam("board", true)) {
            auto board = request->getParam("board", true)->value().toInt();
            _manager->simulateTriggerOnBoard(board);
//            String debugString = "Trigger Board ";
//            debugString += board;
//            _debugHelper->add(debugString);
            request->send(200, "text/plain", "Board triggersd");
        }
    });
    server.on("/", HTTP_GET, [=](AsyncWebServerRequest *request) {
        AsyncResponseStream* response = request->beginResponseStream("text/html");
        response->print(getHomepage());
        request->send(response);

    });
    server.onNotFound(notFound);
    server.begin();
    server.
}

void AccessPoint::loop() {
}