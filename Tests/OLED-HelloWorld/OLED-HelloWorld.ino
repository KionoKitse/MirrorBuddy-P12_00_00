/*
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
//U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9, 8);
//U8GLIB_SH1106_128X64 u8g(13, 11, 10, 12, A0);
U8GLIB_SH1106_128X64 u8g(13, 11, 10, 8, 9);


int Hello = 10;
void setup() {
  u8g.setFont(u8g_font_unifont);
  
}

void loop() {
  Hello ++;

  u8g.firstPage();
  do 
  {
    //u8g.drawStr(0, 10, "HelloWorld");
    char buf[9];
    sprintf (buf, "%d", Hello);
    u8g.drawStr(18, 10, buf);
  } 
  while (u8g.nextPage());
  delay(500);
}
