#ifndef IDIGIT_H
#define IDIGIT_H

#include "stdint.h"

namespace NixieTube
{
    class IDigit
    {
    public:
        virtual ~IDigit() {};

        virtual void SetNumber(uint8_t number) = 0;
        virtual void SetMSD(uint8_t digit) = 0;
        virtual void SetLSD(uint8_t digit) = 0;
    };
}

#endif