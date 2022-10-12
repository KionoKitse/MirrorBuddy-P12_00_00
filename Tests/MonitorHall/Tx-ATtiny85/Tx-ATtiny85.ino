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
byte txValue;
byte test = 10;

//Settings
int configTime = 4000;  //Time to aquire max, min values from hall sensors
int resetTime = 4000;   //If no peaks are detected after this time, the count gets reset

//Define pins
#define hallA         A3  //Data pin of hall sensor A

//Global variables (Peak Detection)
int maxValA;
int minValA;
int thresholdA;
int sensorValA;
bool peakA;
bool lastPeakA;
long refTime;

//Global variables (Rotation Counting)
byte countA;
long lastCountA;

void setup() 
{ 
  //Serial
  mySerial.begin(9600);

  //General pin setup
  pinMode(hallA, INPUT);

  //Variable setup
  lastPeakA = 0;
  countA = 10;
  lastCountA = millis();
  mySerial.write(countA); 

  //Calculate threshold values
  maxValA = 0;
  minValA = 1023;
  refTime = millis();
  while((millis()-refTime) < configTime){
    sensorValA = analogRead(hallA);
    if(sensorValA > maxValA){
        maxValA = sensorValA;
      }
      if(sensorValA < minValA){
        minValA = sensorValA;
      }
  }
  thresholdA = ((maxValA-minValA)/2)+minValA;  
  mySerial.write(9); 
} 
 
void loop() 
{ 
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

  //Reset count
  if((millis()- lastCountA) > resetTime){
    countA = 0;
  }   
}

//Credits
//https://forum.arduino.cc/t/rs485-simple-integer-transfer/619544/13
