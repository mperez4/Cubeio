#include "Cubeio.h"

Cubeio mycube(D6, D1, A1,A2,A3);
char active_side;

void setup(){
  Serial.begin(9600);
  mycube.setThreshold(30);
  mycube.enableLedControl();
  mycube.setLedBrightness(20);
  mycube.attachButton(CHANGE);
}

void loop(){
  if(mycube.buttonPressed()){
    active_side = mycube.getActiveSide();
    mycube.setLedColor(36,100,200);
    Serial.println(active_side);
    delay(250);
  }else{
    mycube.setLedColor(255,255,255);
  }
}