#ifndef WEBINTERFACE_H
#define WEBINTERFACE_H

#include <Configuration.h>

#include <ESPAsyncWebServer.h>

class WebInterface
{
public:
    WebInterface();

    bool AddListener(const char& request);

private:
    AsyncWebServer m_WebServer = AsyncWebServer(80);
};
#endif