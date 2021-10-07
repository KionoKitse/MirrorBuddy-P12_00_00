/*
 * MAX485 ATTiny85
 * DI     0
 * DE     5V
 * RE     5V
 * RO     N/A
 * 
 * POT   Arduino
 * A    GND
 * B    2
 * C    5V
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
  byte angle= map(data, 0, 1023, 0, 180);   
  mySerial.write(angle); 
  delay(50);                           
} 

//Credits
//https://create.arduino.cc/projecthub/maurizfa-13216008-arthur-jogy-13216037-agha-maretha-13216095/modbus-rs-485-using-arduino-c055b5
//https://thewanderingengineer.com/2013/05/05/software-serial-on-the-attiny85/
