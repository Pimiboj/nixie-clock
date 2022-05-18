#ifndef DIGIT_H
#define DIGIT_H

#include "IDigit.h"
#include "stdint.h"

namespace NixieTube
{
    class K155id1 : public IDigit
    {
    private:
        uint8_t m_dataPin;
        uint8_t m_clockPin;
        uint8_t m_latchPin;
        uint8_t m_currentNumber;

    public:
        K155id1(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin);
        
        void SetNumber(uint8_t number);
        void SetMSD(uint8_t digit);
        void SetLSD(uint8_t digit);
    };
}

#endif