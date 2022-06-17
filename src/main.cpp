#include <Arduino.h>
#include <WiFiManager.h>
#include <time.h>
#include <ESPAsyncWebServer.h>

#include <EEPROM.h>
#include <WebInterface.h>

#include <Nixie6Digit.h>
#include <DisplaySimulator.h>
#include <SerialDigit.h>
#include <K155id1.h>
#include <NTP.h>

WiFiServer server(80);

NixieTube::K155id1 HourDigit = NixieTube::K155id1(15, 2, 4);
NixieTube::K155id1 MinuteDigit = NixieTube::K155id1(13, 12, 14);
NixieTube::K155id1 SecondDigit = NixieTube::K155id1(27, 26, 25);
Nixie6Digit display(HourDigit, MinuteDigit, SecondDigit);

//NixieTube::SerialDigit HourDigit = NixieTube::SerialDigit();
//NixieTube::SerialDigit MinuteDigit = NixieTube::SerialDigit();
//NixieTube::SerialDigit SecondDigit = NixieTube::SerialDigit();

//DisplaySimulator display;
NTP ntpClock("europe.pool.ntp.org");

int16_t DSTOffset = 3600;
int16_t TimezoneOffset = 3600;

WebInterface* web;

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

    Serial.println(WiFi.localIP());

    //Start NTP server
    ntpClock.Init();
    web = new WebInterface(server);
    
}

void loop()
{
    struct tm time = ntpClock.GetTimeUTC();
    time.tm_sec += DSTOffset + TimezoneOffset;
    mktime(&time);
    display.DisplayTime(time);
    web->run();
    if(web->Changed())
    {
        DSTOffset = EEPROM.readUShort(DSTOFFSET);
        TimezoneOffset = EEPROM.readULong64(TIMEZONEOFFSET);
        display.SetDisplayBrightness(EEPROM.readUChar(BRIGHTNESS));
        Serial.println(EEPROM.readUChar(BRIGHTNESS));
    }
}