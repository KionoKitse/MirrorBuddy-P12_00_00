//PlotHall > Rx-ATmega328
/*
 * MAX485 Arduino
 * DI     N/A
 * DE     GND
 * RE     GND
 * RO     RX/0
 * 
 * OLED   Arduino
 * GND    GND
 * VDD    5V
 * SCK    13
 * SDA    11
 * RES    9
 * DC     8
 * CS     10
 */


#include "U8glib.h" 
U8GLIB_SH1106_128X64 u8g(13, 11, 10, 8, 9);

//Display limits
const int WIDTH=128;
const int HEIGHT=64;
const int LENGTH=WIDTH;

//X,Y values
int Xid;
int y[LENGTH];
byte ByteData;
int data = 0;
void setup() 
{ 
  //RS485 stuff
  Serial.begin(9600); 
  u8g.setFont(u8g_font_unifont);

  //Empty array
  Xid = 0;
  clearY();
} 
 
void loop() 
{ 
  //Get value from the serial module
  if (Serial.available()) {
    //Get ByteData
    ByteData = Serial.read();
    //Convert into an int
    //data= map(data, 0, 255, 0, 1023); 
    

    //Add data to the points
    //y[Xid] = map(data, 0, 1023, HEIGHT-1, 0);
    y[Xid] = map(ByteData, 0, 255, HEIGHT-1, 0);
    Xid++;
    if(Xid >= WIDTH){
      Xid = 0;
      clearY();
    }
  }
  
  u8g.firstPage();
  do 
  {
    drawY();
  } 
  while (u8g.nextPage());
}  

//Function to clear array of Y values
void clearY(){
  for(int i=0; i<LENGTH; i++){
    y[i] = -1;
  }
}

//Function to draw the Y values
void drawY(){
  u8g.drawPixel(0, y[0]);
  for(int i=1; i<LENGTH; i++){
    if(y[i]!=-1){
      //u8g.drawPixel(i, y[i]);
      u8g.drawLine(i-1, y[i-1], i, y[i]);
    }else{
      break;
    }
  }
}










//Credits
//http://arduino-er.blogspot.com/2015/04/display-waveform-on-mini-oled-with.html
