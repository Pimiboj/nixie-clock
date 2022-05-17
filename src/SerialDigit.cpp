#include "SerialDigit.h"
#include "Arduino.h"
using namespace NixieTube;

SerialDigit::SerialDigit()
{
    //if(!Serial) Serial.begin(9600);
}

void SerialDigit::SetNumber(uint8_t number)
{
    //if(!Serial) Serial.begin(9600);

    Serial.print("Set number to: ");
    Serial.println(number);
}

void SerialDigit::SetMSD(uint8_t digit)
{
    //if(!Serial) Serial.begin(9600);
    
    Serial.print("Set most significat digit to: ");
    Serial.println(static_cast<int>(digit));
}

void SerialDigit::SetLSD(uint8_t digit)
{
    //if(!Serial) Serial.begin(9600);
    
    Serial.print("Set least significant digit to: ");
    Serial.println(static_cast<int>(digit));
}