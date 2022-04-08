#include <K155id1.h>
#include <Arduino.h>
using namespace NixieTube;

K155id1::K155id1(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin) :
    dataPin(dataPin), clockPin(clockPin), latchPin(latchPin)
{
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    isOn = true;
    SetNumber(0);
}
        
void K155id1::SetNumber(uint8_t number)
{
    if(number > 99) return;
    currentNumber = number;
    if(!isOn) return;
    uint8_t data = ((number % 10) << 4) + (number / 10);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, data);
    digitalWrite(latchPin, HIGH);
}

void K155id1::SetMSD(uint8_t digit)
{
    if(digit > 9) return;
    SetNumber(digit * 10 + currentNumber % 10);
}

void K155id1::SetLSD(uint8_t digit)
{
    if(digit > 9) return;
    SetNumber((currentNumber / 10) * 10 + digit);
}