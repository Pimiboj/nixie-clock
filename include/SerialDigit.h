#ifndef SERIALDIGIT_H
#define SERIALDIGIT_H

#include "IDigit.h"
#include "stdint.h"

namespace NixieTube
{
    class SerialDigit : public IDigit
    {
    public:
        SerialDigit();
        
        void SetNumber(uint8_t number);
        void SetMSD(uint8_t digit);
        void SetLSD(uint8_t digit);
    };
}

#endif