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
 * 
 * AT85
 * 1 D5   DI
 * 2 A3   PotA
 * 3 A2   PotB
 * 4 GND  GND
 * 5 D0   LimitA
 * 6 D1   N/A
 * 7 D2   LimitB
 * 8 VCC  VCC
 */

byte tx = 1;
byte rx = 5;
byte PotA = A3;
byte PotB = A2;
byte LimA = 0;
byte LimB = 2;

#include <SoftwareSerial.h>
SoftwareSerial mySerial(rx,tx);
byte txValue;
byte test = 10;

void setup() 
{ 
  pinMode(PotA, INPUT);
  pinMode(PotB, INPUT);
  pinMode(LimA, INPUT);
  pinMode(LimB, INPUT);
  mySerial.begin(9600);
} 
 
void loop() 
{ 
  int ValA = analogRead(PotA);
  int ValB = analogRead(PotB);
  byte LimValA = digitalRead(LimA);
  byte LimValB = digitalRead(LimB);
  byte ByteDataA= map(ValA, 0, 1023, 0, 255);  
  byte ByteDataB= map(ValB, 0, 1023, 0, 255);  
  mySerial.write(ByteDataA); 
  mySerial.write(ByteDataB); 
  mySerial.write(LimValA); 
  mySerial.write(LimValB); 
  delay(10);                           
} 

//Credits
