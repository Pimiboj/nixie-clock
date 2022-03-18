#ifndef DIGIT_H
#define DIGIT_H

#include "stdint.h"
namespace NixieTube
{
    class Digit
    {
    private:
        uint8_t dataPin;
        uint8_t clockPin;
        uint8_t latchPin;
        uint8_t currentNumber;
        bool isOn;

    public:
        Digit(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin);
        
        void SetNumber(uint8_t number);
        void SetMSD(uint8_t digit);
        void SetLSD(uint8_t digit);
    };
}

#endif