#ifndef DISPLAYSIMULATOR_H
#define DISPLAYSIMULATOR_H

#include <stdint.h>
#include <time.h>
#include "IDisplay.h"

class DisplaySimulator : public IDisplay
{
public:
    DisplaySimulator();

    void DisplayTime(struct tm time);
    void SetDisplayBrightness(uint8_t brightness);
};

#endif