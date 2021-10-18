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
//https://create.arduino.cc/projecthub/maurizfa-13216008-arthur-jogy-13216037-agha-maretha-13216095/modbus-rs-485-using-arduino-c055b5
//https://thewanderingengineer.com/2013/05/05/software-serial-on-the-attiny85/
