#include <K155id1.h>
#include <Arduino.h>
using namespace NixieTube;

K155id1::K155id1(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin) :
    m_dataPin(dataPin), m_clockPin(clockPin), m_latchPin(latchPin)
{
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    SetNumber(0);
}
        
void K155id1::SetNumber(uint8_t number)
{
    if(number > 99) return;
    m_currentNumber = number;
    uint8_t data = ((number % 10) << 4) + (number / 10);
    digitalWrite(m_latchPin, LOW);
    shiftOut(m_dataPin, m_clockPin, MSBFIRST, data);
    digitalWrite(m_latchPin, HIGH);
}

void K155id1::SetMSD(uint8_t digit)
{
    if(digit > 9) return;
    SetNumber(digit * 10 + m_currentNumber % 10);
}

void K155id1::SetLSD(uint8_t digit)
{
    if(digit > 9) return;
    SetNumber((m_currentNumber / 10) * 10 + digit);
}