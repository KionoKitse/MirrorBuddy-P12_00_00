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


//Peak Detection
#include <PeakDetection.h>
PeakDetection peakDetection;
#define hallA A3
int sensorVal;
int lastSensorValue;
double data = 0;
int peak = 1;

//Couting
byte count = 0;
int lastState = 0;
//long lastTime = millis();
long deltaTime;
int resetTime = 4000; //If no input for more than 4 seconds the count gets reset


void setup() 
{ 
  mySerial.begin(9600);
  
  pinMode(hallA, INPUT);
  peakDetection.begin();
  
  //Initial calibration time
  lastSensorValue = analogRead(hallA);
  
  /*while(peak != 0){
    SimpleFilter(4);
    data = (double)sensorVal/512-1;
    peakDetection.add(data);
    peak = peakDetection.getPeak();
  }*/
  
} 
 
void loop() 
{ 
  //Read the hall sensor
  //SimpleFilter(4);

  //Peak detection
  sensorVal = analogRead(hallA);
  data = (double)sensorVal/512-1;
  peakDetection.add(data);
  //peak = peakDetection.getPeak();

  //Counting
  //if ((peak > 0) && (lastState != 1)){
  //if (peak > 0){
    //count++;
    //lastTime=millis();
  //}
  //lastState = peak;

  //Reset count
  //if((millis()- lastTime)>resetTime){
    //count=0;
  //}

  //send value
  mySerial.write(count); 
  delay(200);
  count++;
  //int data= analogRead(hallA); 
  //byte ByteData= map(data, 0, 1023, 0, 255);     
  //mySerial.write(ByteData);   
  //delay(10);                           
}
/*
void SimpleFilter(int level){
  //Read sensor
  sensorVal = analogRead(hallA);
  
  //check if filtering is needed
  if(abs(sensorVal-lastSensorValue)<level){
    sensorVal = lastSensorValue;
  }

  //Record last reading
  lastSensorValue = sensorVal;
}
*/
//Credits
//https://github.com/leandcesar/PeakDetection
//https://forum.arduino.cc/t/rs485-simple-integer-transfer/619544/13
