/*
   P12_00_00-Main
   Project: P12_00_00 MirrorBuddy
   
   Notes:
   * This is the code that is running on Pro Mini
   * It is intended to control the motors and monitor the sensors in the mirrors
   * Circuit Js: https://tinyurl.com/2ms5rb3e

   Connections
   PIN   - FUNC - CONNECTION
   Pin 01 - Tx0 - N/C
   Pin 02 - Rx1 - N/C
   Pin 03 - RST - N/C
   Pin 04 - GND - GND
   Pin 05 - D2  - N/C
   Pin 06 - D3  - N/C
   Pin 07 - D4  - RelayA
   Pin 08 - D5  - RelayB
   Pin 09 - D6  - RelayC
   Pin 10 - D7  - RelayD
   Pin 11 - D8  - RelayE
   Pin 12 - D9  - RelayF
   Pin 13 - GND - N/C
   Pin 14 - A6  - N/C
   Pin 15 - A7  - N/C
   Pin 16 - D10 - L_COM
   Pin 17 - D11 - L_LR
   Pin 18 - D12 - UD
   Pin 19 - D13 - R_LR
   Pin 20 - A0  - R_COM
   Pin 21 - A1  - N/C
   Pin 22 - A2  - N/C
   Pin 23 - A3  - N/C
   Pin 24 - A4  - N/C
   Pin 25 - A5  - N/C
   Pin 13 - VCC - 5V Out
   Pin 13 - RST - N/C
   Pin 13 - GND - N/C
   Pin 13 - RAW - 5V RAW

   Hardware
   * 1X ATmega328
   * 1X MAX485 TTL to RS-485
   * 6X Relay
   * 6X Transistor
   * 6x Resistor
   * 12X 1k Resistor

   Credits
   * https://forum.arduino.cc/t/rs485-simple-integer-transfer/619544/13
*/

//MAX485
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,4);  //rx, tx TBD
byte byteData;
byte extractedData;

//Settings
int limitDelay = 2000;  //The amount of time to move a mirror into it's outer most limmit. This is also the time where the sensors are calibrated.
int configTime = 6000;  //Time to aquire max, min values from hall sensors
int resetTime = 4000;   //If no peaks are detected after this time, the count gets reset
int debounceTime = 200; //Time to ignore input for debounce
int syncOffset = 500;   //Slight time offset so both mirrors don't transmit at the same time
byte debug = true;      //Enable debug output


//Global variables (Relay Patterns)
bool L_UP[]   = {0,0,1,1,1,1};
bool L_DOWN[] = {1,1,0,0,0,1};
bool L_LEFT[] = {1,0,1,1,1,1};
bool L_RIGHT[]= {0,1,0,0,0,1};
bool R_UP[]   = {1,1,1,0,0,1};
bool R_DOWN[] = {0,0,0,1,1,1};
bool R_LEFT[] = {1,1,1,0,1,1};
bool R_RIGHT[]= {0,0,0,1,0,1};
bool LR_UP[]  = {0,0,1,0,0,1};

//Global variables (Counting Roations)
char user, lastUser;                                              //Variables to hold which user is present
byte mirrorLDirL, mirrorLDirD, mirrorRDirR, mirrorRDirD;          //Variable to hold the requested number of counts
byte ctMirrorLDirL, ctMirrorLDirD, ctMirrorRDirR, ctMirrorRDirD;  //Variable to hold the current number of counts



void setup()
{
  //Serial
  if(debug)Serial.begin(9600);
  mySerial.begin(9600);

  //Set relay pins as output
  for(byte i=4; i<10; i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,0);
  }

  //Set motor sensor pins as input
  for(byte i=10; i<15; i++){
    pinMode(i,INPUT);
  }

  //Move left mirror to right limit
  if(debug)Serial.println("L_RIGHT");
  SetRelays(L_RIGHT);
  delay(limitDelay);
  ClearRelays();   

  //Move right mirror to left limit
  if(debug)Serial.println("R_LEFT");
  SetRelays(R_LEFT);
  delay(limitDelay);
  ClearRelays(); 

  //Move both mirrors up
  if(debug)Serial.println("LR_UP");
  SetRelays(LR_UP);
  delay(limitDelay);
  ClearRelays(); 

  //Check user and get settings
  if(debug)Serial.println("UserA");
  user = 'A';
  if(user == 'A'){
    mirrorLDirL = 20;
    mirrorLDirD = 30;
    mirrorRDirR = 40;
    mirrorRDirD = 20;
  }
  ctMirrorLDirL = 0;
  ctMirrorLDirD = 0;
  ctMirrorRDirR = 0;
  ctMirrorRDirD = 0;

  //Set left mirror
  if(debug)Serial.println("Set left mirror down");
  SetRelays(L_DOWN);
  while(ctMirrorLDirD <= mirrorLDirD){
    if(mySerial.available()){
      byteData = mySerial.read();
      if(byteData < 127){
        extractedData = byteData; //For the up/down direction the value can only be between (0 <= countA < 127) 
        ctMirrorLDirD = extractedData;
        if(debug){
          Serial.print(byteData);
          Serial.print(",");
          Serial.println(extractedData);
        }
      }
    }
  }
  ClearRelays(); 
  if(debug)Serial.println("Set left mirror left");
  SetRelays(L_LEFT);
  while(ctMirrorLDirL <= mirrorLDirL){
    if(mySerial.available()){
      byteData = mySerial.read();
      if(byteData >= 127){
        extractedData = byteData-127; //For the left/right direction the value can only be between (127 <= countB < 255) 
        ctMirrorLDirD = extractedData;
        if(debug){
          Serial.print(byteData);
          Serial.print(",");
          Serial.println(extractedData);
        }
      }
    }
  }
  ClearRelays(); 

  if(debug)Serial.println("Set right mirror down");
  SetRelays(R_DOWN);
  while(ctMirrorRDirD <= mirrorRDirD){
    if(mySerial.available()){
      byteData = mySerial.read();
      if(byteData < 127){
        extractedData = byteData; //For the up/down direction the value can only be between (0 <= countA < 127) 
        ctMirrorLDirD = extractedData;
        if(debug){
          Serial.print(byteData);
          Serial.print(",");
          Serial.println(extractedData);
        }
      }
    }
  }
  ClearRelays(); 
  if(debug)Serial.println("Set right mirror right");
  SetRelays(R_RIGHT);
  while(ctMirrorRDirR <= mirrorRDirR){
    if(mySerial.available()){
      byteData = mySerial.read();
      if(byteData >= 127){
        extractedData = byteData-127; //For the left/right direction the value can only be between (127 <= countB < 255) 
        ctMirrorLDirD = extractedData;
        if(debug){
          Serial.print(byteData);
          Serial.print(",");
          Serial.println(extractedData);
        }
      }
    }
  }
  ClearRelays(); 

  if(debug)Serial.println("Mirrors Set");

  
  
  
}

void loop()
{


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
