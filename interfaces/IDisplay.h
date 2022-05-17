#ifndef IDISPLAY_H
#define IDISPLAY_H

#include <stdint.h>
#include <time.h>

class IDisplay
{
public:
    virtual ~IDisplay() {};

    virtual void DisplayTime(struct tm time) = 0;
    virtual void SetDisplayBrightness(uint8_t brightness) = 0;
};

#endif