#ifndef NTP_H
#define NTP_H

#include <ITime.h>
#include <ctime>

class NTP : public ITime
{
public:
    NTP(const char* server);

    bool Init();
    bool GetTimeUTC(tm time);

private:
    const char* m_server;
};

#endif