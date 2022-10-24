/*
   P12_00_00-Main
   Project: P12_00_00 MirrorBuddy
   
   Notes:
   * This is the code that is running on the ATtiny85 in the left mirror housing
   * The code is slightly different for the other mirror to prevent collisions on RS485

   Connections
   PIN   - FUNC  - CONNECTION
   Pin 1 - Reset - N/C
   Pin 2 - A3/D3 - OH137 A Up
   Pin 3 - A2/D4 - MAX485(DI)
   Pin 4 - GND   - GND
   Pin 5 - D0    - N/C
   Pin 6 - D1    - N/C
   Pin 7 - A1/D2 - OH137 B Right
   Pin 8 - VCC   - VCC

   Hardware
   * 2X OH137
   * 1X MAX485 TTL to RS-485
   * 1X ATtiny85

   Credits
   * https://forum.arduino.cc/t/rs485-simple-integer-transfer/619544/13
*/

//MAX485
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,4);  //rx, tx

//Settings
int configTime = 6000;  //Time to aquire max, min values from hall sensors
int resetTime = 4000;   //If no peaks are detected after this time, the count gets reset
int debounceTime = 200; //Time to ignore input for debounce
int syncOffset = 500;   //Slight time offset so both mirrors don't transmit at the same time

//Define pins
#define hallA         A3  //Data pin of the hall sensor monitoring the up/down direction motor
#define hallB         A1  //Data pin of the hall sensor monitoring the right/left direction motor

//Global variables (Peak Detection)
long refTime;
int maxValA, minValA, thresholdA, sensorValA;
int maxValB, minValB, thresholdB, sensorValB;
bool peakA, lastPeakA;
bool peakB, lastPeakB;

//Global variables (Rotation Counting)
byte countA, countB;
long lastCountA, lastCountB;

void setup() 
{ 
  //Serial
  mySerial.begin(9600);

  //General pin setup
  pinMode(hallA, INPUT);
  pinMode(hallB, INPUT);

  //Variable setup
  lastPeakA = 0;
  lastPeakB = 0;
  countA = 0;
  countB = 0;
  lastCountA = millis();
  lastCountB = millis();

  //Calculate threshold values
  maxValA = 0;
  maxValB = 0;
  minValA = 1023;
  minValB = 1023;
  refTime = millis();
  while((millis()-refTime) < configTime){
    sensorValA = analogRead(hallA);
    sensorValB = analogRead(hallB);
    if(sensorValA > maxValA) maxValA = sensorValA;
    if(sensorValA < minValA) minValA = sensorValA;
    if(sensorValB > maxValB) maxValB = sensorValB;
    if(sensorValB < minValB) minValB = sensorValB;
  }
  thresholdA = ((maxValA-minValA)/2)+minValA; 
  thresholdB = ((maxValB-minValB)/2)+minValB; 
  
  //Set counts (note: (0 <= countA < 127) & (127 <= countB < 255))
  countA = 0; 
  countB = 127; 

  //Send ready command
  delay(syncOffset);
  mySerial.write(countA); 
  mySerial.write(countB); 
} 
 
void loop() 
{ 
  //Only read from sensor after the debounce time
  if((millis()-lastCountA) > debounceTime){
    //Read from sensor
    sensorValA = analogRead(hallA);
    
    //Peak detection
    peakA = ( sensorValA > thresholdA ) ? 1 : 0;

    //Counting
    if ((peakA > 0) && (lastPeakA != 1)){
      countA++;
      lastCountA=millis();
      
      //Send count 
      mySerial.write(countA); 
    }
    lastPeakA = peakA;

    //Timeout reset count
    if((millis()- lastCountA) > resetTime) countA = 0; 
  
    //Rollover reset count
    if(countA > 125) countA = 0;
  } 

  
  //Only read from sensor after the debounce time
  if((millis()-lastCountB) > debounceTime){
    //Read from sensor
    sensorValB = analogRead(hallB);
    
    //Peak detection
    peakB = ( sensorValB > thresholdB ) ? 1 : 0;

    //Counting
    if ((peakB > 0) && (lastPeakB != 1)){
      countB++;
      lastCountB=millis();
      
      //Send count 
      mySerial.write(countB); 
    }
    lastPeakB = peakB;

    //Timeout reset count
    if((millis()- lastCountB) > resetTime) countB = 127;
  
    //Rollover reset count
    if(countB > 254) countB = 127;
  }  
}
