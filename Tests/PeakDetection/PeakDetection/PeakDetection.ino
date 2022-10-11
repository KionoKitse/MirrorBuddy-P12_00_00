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
 * C      A0
 */

//Peak Detection
#include <PeakDetection.h>
#define pin A0
int sensorVal;
int lastSensorValue;
double data = 0;
int peak = 1;

//Couting
int count = 0;
int lastState = 0;
long lastTime = millis();
long deltaTime;
int resetTime = 4000; //If no input for more than 4 seconds the count gets reset

PeakDetection peakDetection;
void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT);
  peakDetection.begin(48, 3, 0.6);

  //Initial calibration time
  lastSensorValue = analogRead(pin);
  while(peak != 0){
    SimpleFilter(4);
    data = (double)sensorVal/512-1;
    peakDetection.add(data);
    peak = peakDetection.getPeak();
  }
}

void loop() {
  //Read the hall sensor
  SimpleFilter(4);

  //Peak detection
  data = (double)sensorVal/512-1;
  peakDetection.add(data);
  peak = peakDetection.getPeak();

  //Counting
  if ((peak > 0) && (lastState != 1)){
    count++;
    lastTime=millis();
  }
  lastState = peak;

  //Reset count
  if((millis()- lastTime)>resetTime){
    count=0;
  }

  //Plotting
  Serial.print(data);
  Serial.print(",");
  //Serial.print(sensorVal);
  //Serial.print(",");
  Serial.print(count);
  Serial.print(",");
  Serial.println(peak);
}

void SimpleFilter(int level){
  //Read sensor
  sensorVal = analogRead(pin);
  
  //check if filtering is needed
  if(abs(sensorVal-lastSensorValue)<level){
    sensorVal = lastSensorValue;
  }

  //Record last reading
  lastSensorValue = sensorVal;
}

//Credits
//https://github.com/leandcesar/PeakDetection
