#include <Arduino.h>
#include <WiFiManager.h>
#include <time.h>

#include <Nixie6Digit.h>
#include <DisplaySimulator.h>
#include <SerialDigit.h>
#include <K155id1.h>

//NixieTube::K155id1 HourDigit = NixieTube::K155id1(15, 2, 4);
//NixieTube::K155id1 MinuteDigit = NixieTube::K155id1(13, 12, 14);
//NixieTube::K155id1 SecondDigit = NixieTube::K155id1(27, 26, 25);
//Nixie6Digit display(HourDigit, MinuteDigit, SecondDigit);

NixieTube::SerialDigit HourDigit = NixieTube::SerialDigit();
NixieTube::SerialDigit MinuteDigit = NixieTube::SerialDigit();
NixieTube::SerialDigit SecondDigit = NixieTube::SerialDigit();
DisplaySimulator display;


void setup()
{
    //Set up serial and wait for serial to be available
    Serial.begin(9600);
    while(!Serial)
    {

    }

    //Start the WiFi manager and try to connect
    WiFiManager wm;
    wm.autoConnect("NIXIE-CLOCK", "password");
}

void loop()
{
    static uint8_t brightness = 0;
    struct tm time;
    time.tm_hour = 23;
    time.tm_min = 45;
    time.tm_sec = 59;
    display.SetDisplayBrightness(brightness);
    display.DisplayTime(time);
    delay(1000);
    brightness = brightness + 10;
}