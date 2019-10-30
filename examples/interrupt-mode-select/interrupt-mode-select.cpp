//creates a button interrupt with onboard hardware, 
//and sets it as a mode selector

#include "Cubeio.h"

Cubeio mycube(D6, D1, A1,A2,A3);

int _case = 0;
unsigned long start_time;
unsigned long current_time;
unsigned long elapsed_time;
const int mode_threshold = 2000;

int modeSelect(int current_case);
void modeHandler(void);

void setup(){
  Serial.begin(9600);
  mycube.enableLedControl();
  mycube.setLedBrightness(20);
  mycube.attachButton(CHANGE);
}

void loop(){
  modeHandler();
  switch (_case){
    case 1:
      mycube.setLedColor(0,255,0);
    break;
    case 2: 
      mycube.setLedColor(255,0,0);
    break;
    default:
      mycube.setLedColor(255,255,255);
    break;
  }
}

//listens for either a short(two seconds) press, a long(four seconds) press, or
//a longest(six seconds) press and returns a value that is used in a switch statment
int modeSelect(int current_case){
  if(elapsed_time > mode_threshold && elapsed_time < mode_threshold * 2){
    mycube.setLedColor(0,255,0);
    return 1;
  }if(elapsed_time > mode_threshold * 2 && elapsed_time < mode_threshold * 3){
    mycube.setLedColor(255,0,0);
    return 2;
  }if(elapsed_time > mode_threshold * 3 && elapsed_time < mode_threshold * 4){
    mycube.setLedColor(255,255,255);
    return 0;
  }else{
    return current_case;
  }
}
//unfortunately we cannot make a handler while using interrupts,
//so the function needs to be called.
void modeHandler(){
  if(mycube.buttonPressed()){
    start_time = millis();
    elapsed_time =  start_time - current_time;
    _case = modeSelect(_case);
  }else{
    current_time = millis();
  }
}