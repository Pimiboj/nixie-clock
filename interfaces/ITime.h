#ifndef ICLOCK_H
#define ICLOCK_H

#include <time.h>

class ITime
{
public:
    virtual ~ITime() {};

    virtual tm GetTimeUTC() = 0;
};

#endif