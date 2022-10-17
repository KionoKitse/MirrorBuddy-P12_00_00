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
byte byteData= 5;
byte hallA;
byte hallB;

void setup()
{
    Serial.begin(9600); 
    mySerial.begin(9600);
    hallA = 0;
    hallB = 0;
}

void loop()
{
    if( mySerial.available() )  
    {
      byteData = mySerial.read();
      if(byteData < 127){ 
        hallA = byteData;
      }else{
        hallB = byteData - 127;
      }
      
      //Serial.println(ByteData);
    }
    
    Serial.print(hallA);
    Serial.print(',');
    Serial.println(hallB);
    
    //Serial.print(analogRead(A0));
    //Serial.print(',');
    //Serial.println(analogRead(A1));
}
//Credits
//https://forum.arduino.cc/t/rs485-simple-integer-transfer/619544/13
