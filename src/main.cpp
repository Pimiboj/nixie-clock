#include <Arduino.h>
#include <K155id1.h>

NixieTube::K155id1 HourDigit = NixieTube::K155id1(15, 2, 4);
NixieTube::K155id1 MinuteDigit = NixieTube::K155id1(13, 12, 14);
NixieTube::K155id1 SecondDigit = NixieTube::K155id1(27, 26, 25);

void setup()
{
    HourDigit.SetNumber(12);
    MinuteDigit.SetNumber(34);
    SecondDigit.SetNumber(56);
    delay(2000);
}

void loop()
{
    for(int i = 0; i < 10; i++)
    {
        HourDigit.SetNumber(i*11);
        MinuteDigit.SetNumber(i*11);
        SecondDigit.SetNumber(i*11);
        delay(1000);
    }
}