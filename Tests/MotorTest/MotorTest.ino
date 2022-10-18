//MonitorHall > Rx-ATmega328
/*
 * Relay board  Arduino
 * RelayA       D4
 * RelayB       D5
 * RelayC       D6
 * RelayD       D7
 * RelayE       D8
 * RelayF       D9 
 * L_COM        D10
 * L_LR         D11
 * UD           D12 
 * R_LR         D13
 * R_COM        D14/A0
 * 
 * Circuit Js: https://tinyurl.com/2ms5rb3e
 */

bool L_UP[]   = {0,0,1,1,1,1};
bool L_DOWN[] = {1,1,0,0,0,1};
bool L_LEFT[] = {1,0,1,1,1,1};
bool L_RIGHT[]= {0,1,0,0,0,1};
bool R_UP[]   = {1,1,1,0,0,1};
bool R_DOWN[] = {0,0,0,1,1,1};
bool R_LEFT[] = {1,1,1,0,1,1};
bool R_RIGHT[]= {0,0,0,1,0,1};

#define hallA A0
int sensorVal;
long refTime;
int maxVal;
int minVal;
int threshold;
int peak;

int stall = 500;
int runing = 5000;
void setup()
{
  //Serial
  Serial.begin(9600);
  
  //Set relay pins as output
  for(byte i=4; i<10; i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,0);
  }
  
  //Set motor sensor pins as input
  for(byte i=10; i<15; i++){
    pinMode(i,INPUT);
  }
  
}

void loop()
{
  //L_UP
  Serial.println("L_UP");
  SetRelays(L_UP);
  delay(runing);
  ReadSensors();
  ClearRelays();
  delay(stall);
  
  //L_DOWN
  Serial.println("L_DOWN");
  SetRelays(L_DOWN);
  delay(runing);
  ReadSensors();
  ClearRelays();
  delay(stall);

  //L_LEFT
  Serial.println("L_LEFT");
  SetRelays(L_LEFT);
  delay(runing);
  ReadSensors();
  ClearRelays();
  delay(stall);

  //L_RIGHT
  Serial.println("L_RIGHT");
  SetRelays(L_RIGHT);
  delay(runing);
  ReadSensors();
  ClearRelays();
  delay(stall);
  
  //R_UP
  Serial.println("R_UP");
  SetRelays(R_UP);
  delay(runing);
  ReadSensors();
  ClearRelays();
  delay(stall);

  //R_DOWN
  Serial.println("R_DOWN");
  SetRelays(R_DOWN);
  delay(runing);
  ReadSensors();
  ClearRelays();
  delay(stall);

  //R_LEFT
  Serial.println("R_LEFT");
  SetRelays(R_LEFT);
  delay(runing);
  ReadSensors();
  ClearRelays();
  delay(stall);

  //R_RIGHT
  Serial.println("R_RIGHT");
  SetRelays(R_RIGHT);
  delay(runing);
  ReadSensors();
  ClearRelays();
  delay(stall);
  
}

void SetRelays(bool arraySet[6]){
  for(byte i=0; i<6; i++){
    digitalWrite(i+4,arraySet[i]);
    Serial.print(arraySet[i]);
    Serial.print(",");
  }
  Serial.println();
}
void ReadSensors(){
  for (byte i=10; i<15;i++){
    Serial.print(digitalRead(i));
    Serial.print(",");
  }
  Serial.println("");
  Serial.println("");
}
void ClearRelays(){
  for(byte i=4; i<10; i++){
    digitalWrite(i,0);
  }
}
//Credits
