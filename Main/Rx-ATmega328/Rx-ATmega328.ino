byte tx = 4;
byte rx = 3;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(rx,tx);
byte RxVal = 3;

void setup()
{
    Serial.begin(9600); 
    mySerial.begin(9600);
    
}//setup

void loop()
{
    if( mySerial.available() )  
    {
      RxVal = mySerial.read();
    }
    Serial.println(RxVal);

}
//Credits
//https://forum.arduino.cc/t/rs485-simple-integer-transfer/619544/13
