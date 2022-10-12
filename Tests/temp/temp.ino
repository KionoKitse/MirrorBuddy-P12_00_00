//MonitorHall > Rx-ATmega328
/*
 * MAX485 Arduino
 * DI     N/A
 * DE     GND
 * RE     GND
 * RO     D3
 */






#define hallA A0
int sensorVal;
long refTime;
int maxVal;
int minVal;
int threshold;
int peak;


void setup()
{
    Serial.begin(9600); 
    maxVal = 0;
    minVal = 1023;
    threshold = 512;
    refTime = millis();

    while((millis()-refTime) < 10000){
      //Read sensor
      sensorVal = analogRead(hallA);
      //Set limits
      if(sensorVal > maxVal){
        maxVal = sensorVal;
      }
      if(sensorVal < minVal){
        minVal = sensorVal;
      }
      threshold = ((maxVal-minVal)/2)+minVal;
      if(sensorVal < threshold){
        peak = minVal+10;
      }else{
        peak = maxVal-10;
      }
      //Plot results
      /*
      Serial.print(sensorVal);
      Serial.print(",");
      Serial.print(minVal);
      Serial.print(",");
      Serial.print(threshold);
      Serial.print(",");
      Serial.print(maxVal);
      Serial.print(",");
      Serial.println(peak);
      */
    }
}

void loop()
{
  sensorVal = analogRead(hallA);
  if(sensorVal < threshold){
    peak = minVal+10;
  }else{
    peak = maxVal-10;
  }
  Serial.print(sensorVal);
  Serial.print(",");
  Serial.print(threshold);
  Serial.print(",");
  Serial.println(peak);
}
//Credits
