//creates a button interrupt with onboard hardware, 
//and sets it as a mode selector

#include "Cubeio.h"

Cubeio mycube(D6, D1, A1,A2,A3);

int _case = 0;
unsigned long start_time;
unsigned long current_time;
unsigned long elapsed_time;
int modeSelect(int self_state);

bool state = false;

void setup(){
  Serial.begin(9600);
  mycube.enableLedControl();
  mycube.setLedBrightness(20);
  mycube.attachButton(CHANGE);
}

void loop(){
  _case = modeSelect(_case);
}

int modeSelect(int self_state){
  const int mode_threshold = 3000;
  current_time = millis();
  elapsed_time = current_time - start_time;

  if(mycube.buttonPressed()){
    Serial.println(state);
    state = !state;
    start_time = millis();
    mycube.setLedColor(36,100,200);
  }else{
    mycube.setLedColor(255,255,255);
  }
  if(elapsed_time > mode_threshold && elapsed_time < mode_threshold * 2 && state){
    Serial.println("Button was pressed for three seconds");
    mycube.setLedColor(255,100,20);
    state = false;
  }
  return self_state;
}