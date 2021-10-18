//MonitorHall > Tx-ATtiny85
/*
 * MAX485 ATTiny85
 * DI     0
 * DE     5V
 * RE     5V
 * RO     N/A
 * 
 * OH137  Arduino
 * A      5V
 * B      GND
 * C      A1
 */


#include <SoftwareSerial.h>
SoftwareSerial mySerial(1,0);  //rx, tx
byte txValue;
byte test = 10;

void setup() 
{ 
  pinMode(A1, INPUT);
  mySerial.begin(9600);
} 
 
void loop() 
{ 
  int data= analogRead(A1); 
  byte ByteData= map(data, 0, 1023, 0, 255);     
  mySerial.write(ByteData);   
  delay(10);                           
} 

//Credits
//https://forum.arduino.cc/t/rs485-simple-integer-transfer/619544/13
