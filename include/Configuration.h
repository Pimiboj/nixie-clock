#ifndef CONFIGURATION_H
#define CONFIGUTATION_H

#include <vector>
#include <stdint.h>

#define HASCHANGED 0
#define TIMEZONEOFFSET 1
#define DSTOFFSET 9
#define BRIGHTNESS 11

struct Configuration
{
    bool HasChanged = false;
    int64_t TimeZoneOffset = 0;
    int16_t DaylightSavingsTimeOffset = 0;
    bool DynamicBrightness = false;
    uint8_t StaticBrightness = 0;
    //std::vector<std::pair<uint16_t, uint8_t>> DynamicBrightness; //Time in minutes, Brightness 0 - 255
};

#endif