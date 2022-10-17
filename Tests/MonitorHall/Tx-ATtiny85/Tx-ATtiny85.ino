//MonitorHall > Tx-ATtiny85
/*
 * MAX485 ATTiny85
 * DI     Pin0
 * DE     5V
 * RE     5V
 * RO     N/A Pin1 is software serial
 * 
 * OH137  ATTiny85 (Hall A)
 * A      5V
 * B      GND
 * C      A3
 * 
 * OH137  ATTiny85 (Hall B)
 * A      5V
 * B      GND
 * C      A2
 */

//MAX485
#include <SoftwareSerial.h>
SoftwareSerial mySerial(1,0);  //rx, tx

//Settings
int configTime = 1000;  //Time to aquire max, min values from hall sensors
int resetTime = 4000;   //If no peaks are detected after this time, the count gets reset
int debounceTime = 200; //Time to ignore input for debounce
 
//Define pins
#define hallA         A3  //Data pin of hall sensor A
#define hallB         A2  //Data pin of hall sensor B

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

//Credits
//https://forum.arduino.cc/t/rs485-simple-integer-transfer/619544/13
