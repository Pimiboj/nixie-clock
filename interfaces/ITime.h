#ifndef ICLOCK_H
#define ICLOCK_H

#include <time.h>

class ITime
{
public:
    virtual ~ITime() {};

    virtual bool GetTimeUTC(tm time) = 0;
};

#endif