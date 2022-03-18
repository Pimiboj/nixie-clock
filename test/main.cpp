#include <Arduino.h>
#include <Digit.h>

NixieTube::Digit HourDigit = NixieTube::Digit(15, 2, 4);
NixieTube::Digit MinuteDigit = NixieTube::Digit(13, 12, 14);
NixieTube::Digit SecondDigit = NixieTube::Digit(27, 26, 25);

void setup() {
    HourDigit.SetNumber(12);
    MinuteDigit.SetNumber(34);
    SecondDigit.SetNumber(56);
}