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
  for(int i=4; i<10; i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
}

void loop()
{
  for(int i=4; i<10; i++){
    digitalWrite(i,HIGH);
    delay(1000);
  }
  delay(2000);
  for(int i=9; i>0; i--){
    digitalWrite(i,LOW);
    delay(1000);
  }
  delay(2000);

}
//Credits
