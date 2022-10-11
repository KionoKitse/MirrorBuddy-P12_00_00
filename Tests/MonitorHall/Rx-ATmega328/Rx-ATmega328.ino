//MonitorHall > Rx-ATmega328
/*
 * MAX485 Arduino
 * DI     N/A
 * DE     GND
 * RE     GND
 * RO     D3
 */





#include <SoftwareSerial.h> 
SoftwareSerial mySerial(3,4);  //rx, tx  
int Result = 500;
byte ByteData= 5;

void setup()
{
    Serial.begin(9600); 
    mySerial.begin(9600);
}

void loop()
{
    if( mySerial.available() )  
    {
      ByteData = mySerial.read();
      //Serial.println(ByteData);
    }
    Serial.println(ByteData);
    //Serial.println(analogRead(A1));
}
//Credits
//https://forum.arduino.cc/t/rs485-simple-integer-transfer/619544/13
