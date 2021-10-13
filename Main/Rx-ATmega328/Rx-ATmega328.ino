#include "U8glib.h" 
U8GLIB_SH1106_128X64 u8g(13, 11, 10, 8, 9);

int Result = 500;
#define BUFF_SIZE       10
byte
    rxIdx,
    rxBuff[BUFF_SIZE];
    
void setup()
{
    Serial.begin(9600); 
  u8g.setFont(u8g_font_unifont);
    rxIdx = 0;
    
}//setup

void loop()
{
    if( Serial.available() )  
    {
        do
        {
            rxBuff[rxIdx] = Serial.read();
            rxIdx++;
            if( rxIdx == 2 )
            {
                Result = (rxBuff[0] << 8) + rxBuff[1];
                Serial.print( "Received: " ); Serial.println( Result );
                rxIdx = 0;   
            }
        }
    while( Serial.available() );
    }
  u8g.firstPage();
  do 
  {
    char buf[3];
    sprintf (buf, "%d", Result);
    u8g.drawStr(18, 10, buf);
  } 
  while (u8g.nextPage());
}
//Credits
//https://forum.arduino.cc/t/rs485-simple-integer-transfer/619544/13
