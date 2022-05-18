#include "NTP.h"

#include <WiFi.h>
#include <time.h>

NTP::NTP(const char* server)
    : m_server(server)
{

}

bool NTP::Init()
{
    configTime(0, 0, m_server);
    return true;
}

tm NTP::GetTimeUTC()
{
    struct tm timeInfo;
    getLocalTime(&timeInfo);
    return timeInfo;
}