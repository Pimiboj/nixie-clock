#include "WebInterface.h"

#include <EEPROM.h>

String processor(const String &var)
{
    if (var == "TIMEZONE") {
        return String((long)EEPROM.readLong64(TIMEZONEOFFSET), DEC);
    } else if (var == "DST") {
        return String(EEPROM.readLong(DSTOFFSET), DEC);
    } else if (var == "BRIGHTNESS") {
        return String(EEPROM.readByte(BRIGHTNESS), DEC);
    }

    return String();
}

//const char index_html[] PROGMEM = "<!DOCTYPE HTML><html><head><title>ESP Web Server</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\"><style>html {font-family: Arial; display: inline-block; text-align: center;}h2 {font-size: 3.0rem;}p {font-size: 3.0rem;}body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}.switch {position: relative; display: inline-block; width: 120px; height: 68px} .switch input {display: none}.slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}.slider:before {position: absolute; content: \"\"; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}input:checked+.slider {background-color: #b30000}input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}</style></head><body><h2>ESP Web Server</h2><p1>%TIMEZONE%</p1></body></html>)";
const char index_html[] = "<p1>hoi</p1>";

void timeHandler(AsyncWebServerRequest *request)
{
    if(request->hasParam("timezone"))
    {
        EEPROM.write(TIMEZONEOFFSET, request->getParam("timezone")->value().toInt());
        Serial.println("EEPROM WRITEN TIMEZONE");
    }
    if(request->hasParam("dst"))
    {
        EEPROM.write(DSTOFFSET, (uint16_t)request->getParam("dst")->value().toInt());
        Serial.println("EEPROM WRITEN DST");
    }
    return;
}

void brightnessHandler(AsyncWebServerRequest *request)
{
    if(request->hasParam("brightness"))
    {
        EEPROM.write(BRIGHTNESS, (uint8_t)request->getParam("brightness")->value().toInt());
        Serial.println("EEPROM WRITEN BRIGHTNESS");
    }
    return;
}

void onNotFound(AsyncWebServerRequest *request) {
    request->send(404);
}

void onRootRequest(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html, processor);
}

WebInterface::WebInterface()
{
    m_WebServer.on("/", HTTP_GET, onRootRequest);
    m_WebServer.onNotFound(onNotFound);
    m_WebServer.on("/Time", timeHandler);
    m_WebServer.on("/Brighness", brightnessHandler);

    m_WebServer.begin();
    Serial.println("WEBSERVER INIT");
}