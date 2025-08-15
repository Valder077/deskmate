#include <Arduino.h>
#include <U8g2lib.h> 
#include <Wire.h>   

#define COUNTDOWN_TIME  (25ul * 60ul * 1000ul) 

char szString[20];
byte mins, secs;
bool colonVisible = true;

unsigned long
    timeTemp,
    timeNow,
    timeStart,
    timeElapsed,
    timeLeft;


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup()
{
    u8g2.begin();
    Serial.begin(9600);
    timeStart = millis();
    mins = 25;
    secs = 0;
}

void DoCountdown()
{
    static byte lastsecs = 255; 

    timeNow = millis();
    timeElapsed = timeNow - timeStart;

    if (mins == 0 && secs == 0)
        return;

    timeLeft = COUNTDOWN_TIME - timeElapsed;

    mins = (byte)(timeLeft / 60000ul);
    timeTemp = timeLeft - (mins * 60000);
    secs = (byte)(timeTemp / 1000ul);

    if (mins == 0 && secs == 0)
    {
        sprintf(szString, "**DONE**");
        Serial.println(szString);

        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_ncenB14_tr); 
        u8g2.drawStr(30, 40, szString);
        u8g2.sendBuffer();
    }
    else if (secs != lastsecs)
    {
        lastsecs = secs;

        
        colonVisible = !colonVisible;

        if (colonVisible)
            sprintf(szString, "%02d:%02d", mins, secs);
        else
            sprintf(szString, "%02d %02d", mins, secs); 

        Serial.println(szString);

        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_ncenB14_tr);
        u8g2.drawStr(40, 40, szString);
        u8g2.sendBuffer();
    }
}

void loop()
{
    DoCountdown();
}