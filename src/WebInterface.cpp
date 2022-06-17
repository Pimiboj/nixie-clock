#include "WebInterface.h"

#include <EEPROM.h>
#include <WiFi.h>

WebInterface::WebInterface(WiFiServer& server)
    : server(server)
{
    server.begin();
    EEPROM.begin(30);
    m_timezone = EEPROM.readULong64(TIMEZONEOFFSET) / 3600;
    m_brightness = EEPROM.readUChar(BRIGHTNESS);
    if(EEPROM.readUShort(DSTOFFSET) / 3600 == 0)
    {
        m_dstActive = false;
    }
    else{
        m_dstActive = true;
    }
}

void WebInterface::run()
{
    WiFiClient client = server.available(); // Listen for incoming clients
    if (client)
    { // If a new client connects,
        currentTime = millis();
        previousTime = currentTime;
        Serial.println("New Client."); // print a message out in the serial port
        String currentLine = "";       // make a String to hold incoming data from the client
        while (client.connected() && currentTime - previousTime <= timeoutTime)
        { // loop while the client's connected
            currentTime = millis();
            if (client.available())
            {                           // if there's bytes to read from the client,
                char c = client.read(); // read a byte, then
                Serial.write(c);        // print it out the serial monitor
                header += c;
                if (c == '\n')
                { // if the byte is a newline character
                    if (currentLine.length() == 0)
                    {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();
                        if (header.indexOf("GET /summertime/active") >= 0)
                        {
                            m_dstActive = true;
                            EEPROM.writeUShort(DSTOFFSET, 3600);
                            EEPROM.commit();
                            m_changed = true;
                        }
                        else if (header.indexOf("GET /summertime/inactive") >= 0)
                        {
                            m_dstActive = false;
                            EEPROM.writeUShort(DSTOFFSET, 0);
                            EEPROM.commit();
                            m_changed = true;
                        }

                        else if (header.indexOf("GET /dayincrease") >= 0)
                        {
                            m_brightness += 20;
                            EEPROM.writeUChar(BRIGHTNESS, m_brightness);
                            EEPROM.commit();
                            m_changed = true;
                        }
                        else if (header.indexOf("GET /daydecrease") >= 0)
                        {
                            m_brightness -= 20;
                            EEPROM.writeUChar(BRIGHTNESS, m_brightness);
                            EEPROM.commit();
                            m_changed = true;
                        }

                        else if (header.indexOf("GET /timeincrease") >= 0)
                        {
                            if(m_timezone < 12)
                            {
                                m_timezone++;
                            }
                            EEPROM.writeULong64(TIMEZONEOFFSET, m_timezone*3600);
                            
                            EEPROM.commit();
                            m_changed = true;
                        }
                        else if (header.indexOf("GET /timedecrease") >= 0)
                        {
                            if(m_timezone > -12)
                            {
                                m_timezone--;
                            }
                            EEPROM.writeULong64(TIMEZONEOFFSET, m_timezone*3600);
                            EEPROM.commit();
                            m_changed = true;
                        }

                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #FF8000; border: none; color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println(".button2 {background-color: #555555;}</style></head>");
                        client.println("<body><h1>Smart Nixie configuration page</h1>");
                        client.println("<p>Summertime Status: summerTime</p>");
                        if (!m_dstActive)
                        {
                            client.println("<p><a href=\"/summertime/active\"><button class=\"button\">Activate</button></a></p>");
                        }
                        else
                        {
                            client.println("<p><a href=\"/summertime/inactive\"><button class=\"button button2\">Deactivate</button></a></p>");
                        }
                        client.println("<body><h1>Brightness</h1>");
                        client.println("<p>Current brightness (0-10): " + String(m_brightness) + "</p>");
                        client.println("<p><a href=\"/dayincrease\"><button class=\"button\">Increase</button></a></p>");
                        client.println("<p><a href=\"/daydecrease\"><button class=\"button\">Decrease</button></a></p>");

                        client.println("<body><h1>Time Zone</h1>");
                        client.println("<p>Current timezone (-12, 12): " + String(m_timezone) + "</p>");
                        client.println("<p><a href=\"/timeincrease\"><button class=\"button\">Increase</button></a></p>");
                        client.println("<p><a href=\"/timedecrease\"><button class=\"button\">Decrease</button></a></p>");

                        client.println("<p>Position: <span id=\"servoPos\"></span></p>");
                        //client.println("<input type=\"range\" min=\"0\" max=\"256\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\"150\"/>");
                        client.println("<script>var slider = document.getElementById(\"servoSlider\");");
                        client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
                        client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
                        client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
                        client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");
                        client.println("</body></html>");
                        client.println();
                        break;
                    }
                    else
                    {
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {
                    currentLine += c;
                }
            }
        }
        header = "";
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}

bool WebInterface::Changed()
{
    if(m_changed)
    {
        Serial.println("CHANGE TRUE");
        m_changed = false;
        return true;
    }
    return false;
}