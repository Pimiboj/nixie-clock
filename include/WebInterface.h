#ifndef WEBINTERFACE_H
#define WEBINTERFACE_H

#include <Configuration.h>

#include <ESPAsyncWebServer.h>

class WebInterface
{
public:
    WebInterface(WiFiServer& server);

    void run();
    bool Changed();

private:
    unsigned long currentTime = millis();
    unsigned long previousTime = 0;
    const long timeoutTime = 2000;
    String header;
    WiFiServer& server;
    bool m_changed = false;
    bool m_dstActive = true;
    uint8_t m_brightness = 255;
    int8_t m_timezone = 1;
};
#endif