//MonitorHall > Rx-ATmega328
/*
 * MAX485 Arduino
 * DI     N/A
 * DE     GND
 * RE     GND
 * RO     RX/0
 * 
 * OLED   Arduino
 * GND    GND
 * VDD    5V
 * SCK    13
 * SDA    11
 * RES    9
 * DC     8
 * CS     10
 */

#include "U8glib.h" 
U8GLIB_SH1106_128X64 u8g(13, 11, 10, 8, 9);

int Result = 500;
byte ByteData;

#include <SoftwareSerial.h> 
SoftwareSerial mySerial(3,4);  //rx, tx  
void setup()
{
    Serial.begin(9600); 
    mySerial.begin(9600);
    u8g.setFont(u8g_font_unifont);
}

void loop()
{
    if( mySerial.available() )  
    {
      ByteData = mySerial.read();
      Result= map(ByteData, 0, 255, 0, 1023); 
    }
    Serial.println(Result);
}
//Credits
//https://forum.arduino.cc/t/rs485-simple-integer-transfer/619544/13
