#include "Nixie6Digit.h"

#include <Arduino.h>

Nixie6Digit::Nixie6Digit(NixieTube::IDigit& hourDigit, NixieTube::IDigit& minuteDigit, NixieTube::IDigit& SecondDigit)
    :m_hourDigit(hourDigit), m_minuteDigit(minuteDigit), m_secondDigit(SecondDigit)
{
    ledcAttachPin(23, 0);
    ledcSetup(0, 1000, 8);
}

void Nixie6Digit::DisplayTime(struct tm time)
{
    m_hourDigit.SetNumber(time.tm_hour);
    m_minuteDigit.SetNumber(time.tm_min);
    m_secondDigit.SetNumber(time.tm_sec);
}

void Nixie6Digit::SetDisplayBrightness(uint8_t brightness)
{
    uint8_t mappedBrigtness = map(brightness, 255, 0, 0, 160);
    ledcWrite(0, mappedBrigtness);
}