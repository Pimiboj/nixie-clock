#include "DisplaySimulator.h"

#include <Arduino.h>

DisplaySimulator::DisplaySimulator()
{
    Serial.begin(115200);
}

void DisplaySimulator::DisplayTime(struct tm time)
{
    Serial.print("Time set to : ");
    Serial.print(time.tm_hour);
    Serial.print(":");
    Serial.print(time.tm_min);
    Serial.print(":");
    Serial.println(time.tm_sec);
}

void DisplaySimulator::SetDisplayBrightness(uint8_t brightness)
{
    Serial.print("Display brightness set to: ");
    Serial.print(brightness);
}