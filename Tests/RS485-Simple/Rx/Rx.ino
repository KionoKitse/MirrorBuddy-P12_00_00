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

byte angle = 0;
 
void setup() 
{ 
  Serial.begin(9600); 
  u8g.setFont(u8g_font_unifont);
} 
 
void loop() 
{ 
  if (Serial.available()) {
    angle = Serial.read();
  }
  
  u8g.firstPage();
  do 
  {
    char buf[3];
    sprintf (buf, "%d", angle);
    u8g.drawStr(18, 10, buf);
  } 
  while (u8g.nextPage());
}  
//Credits
//https://create.arduino.cc/projecthub/maurizfa-13216008-arthur-jogy-13216037-agha-maretha-13216095/modbus-rs-485-using-arduino-c055b5
