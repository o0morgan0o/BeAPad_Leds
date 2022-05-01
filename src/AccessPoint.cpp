#include "AccessPoint.h"

AccessPoint::AccessPoint() {
    WiFiClass::mode(WIFI_AP);
    WiFi.softAP(_ssid, _password);

}

void AccessPoint::init(LedBoardsManager *manager, Debug_Helper *debugHelper) {
    _debugHelper = debugHelper;
    _manager = manager;
    //
    _debugHelper->logWifiInit(WiFi.softAPIP().toString());

    // ****************************
    // BEGIN OF ROUTES
    // ****************************

    server.on("/", HTTP_GET, [this]() {
        server.send(200, "text/html", getHomepage());
    });
    //
    server.on("/trigger", HTTP_GET, [this]() {
        for (uint8_t i = 0; i < server.args(); i++) {
            if (server.argName(i) == "board") {
                auto board = server.arg(i).toInt();
                _manager->triggerBoard(board);
                String message = "parameter Board Found ! ";
                message += board;
                return server.send(200, "text/plain", message);
            }
        }
        server.send(404, "text/plain", "Board Parameter Not Found !");
    });
    //
    server.on("/debug_on", HTTP_GET, [this]() {
        _debugHelper->setDEBUGLights(true);
        server.send(200, "text/html", getHomepage());
    });
    //
    server.on("/debug_off", HTTP_GET, [this]() {
        _debugHelper->setDEBUGLights(false);
        server.send(200, "text/html", getHomepage());
    });

    // ****************************
    // END OF ROUTES
    // ****************************

    server.onNotFound([this]() {
        String message = "File Not Found\n\n";
        message += "URI: ";
        message += server.uri();
        message += "\nMethod: ";
        message += (server.method() == HTTP_GET) ? "GET" : "POST";
        message += "\nArguments: ";
        message += server.args();
        message += "\n";
        for (uint8_t i = 0; i < server.args(); i++) {
            message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
        }
        server.send(404, "text/plain", message);
    });
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

}

void AccessPoint::loop() {
    server.handleClient();

}