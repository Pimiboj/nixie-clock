#ifndef NIXIE6DIGIT_H
#define NIXIE6DIGIT_H

#include <stdint.h>
#include <time.h>
#include "IDigit.h"
#include "IDisplay.h"

class Nixie6Digit : public IDisplay
{
public:
    Nixie6Digit(NixieTube::IDigit& hourDigit, NixieTube::IDigit& minuteDigit, NixieTube::IDigit& SecondDigit);

    void DisplayTime(struct tm time);
    void SetDisplayBrightness(uint8_t brightness);

private:
    NixieTube::IDigit& m_hourDigit;
    NixieTube::IDigit& m_minuteDigit;
    NixieTube::IDigit& m_secondDigit;
};

#endif