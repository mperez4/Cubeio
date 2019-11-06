//creates a button interrupt with onboard hardware, 
//and sets it as a mode selector

#include "Cubeio.h"

Cubeio mycube(D6, D1, A1,A2,A3);

int _case = 0;
unsigned long start_time;
unsigned long current_time;
unsigned long elapsed_time;
const int mode_threshold = 2000;

int active_side;
int session_list[2];
bool isRegistered = false;
bool isRegistering = false;
bool button_state = false;
static volatile int registry = 0;
static volatile int registry_size = 2;
String registration_id;

String status = "unpaired"; //particle variable to manage status

int registrationResponse(String command);
int modeSelect(int current_case);
void modeHandler(void);

void setup(){
  Serial.begin(9600);
  Particle.variable("status", status);
  Particle.function("registration_response", registrationResponse);
  mycube.enableLedControl();
  mycube.setLedBrightness(20);
  mycube.attachButton(CHANGE);
  mycube.setThreshold(30);
}

void loop(){
  active_side = mycube.getActiveSide();
  modeHandler();
  switch (_case){
    case 1://registration mode
      mycube.setLedColor(0,255,0);
      //collects sequence of two numbers, sends it to particle. backend responds
      //with a 0 or 1
      if (registry >= registry_size){
        Serial.println("Exiting registration mode...");
        isRegistering = false;
        registry = 0;
        for(int i = 0; i <= registry_size; i++){
          registration_id.concat(session_list[i]);
        }
        Particle.publish("reg_id", registration_id);
        registration_id = "";
      }
    break;
    case 2://is registered
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
  //registration mode
  if(elapsed_time > mode_threshold && elapsed_time < mode_threshold * 2 && !isRegistering){
    mycube.setLedColor(0,255,0);
    isRegistering = true;
    return 1;
  }
  if(elapsed_time > mode_threshold * 2 && elapsed_time < mode_threshold * 3 && !isRegistering){
    mycube.setLedColor(255,0,0);
    return 2;
  }
  if(elapsed_time > mode_threshold * 3 && elapsed_time < mode_threshold * 4 && !isRegistering){
    mycube.setLedColor(255,255,255);
    return 0;
  }
  else{
    return current_case;
  }
}
//unfortunately we cannot make a handler while using interrupts,
//so the function needs to be called.
void modeHandler(){
  _case = modeSelect(_case);
  if(mycube.buttonPressed()){
    start_time = millis();
    elapsed_time =  start_time - current_time;
    if(isRegistering){
      session_list[registry] = active_side;
      Serial.printlnf("Registered: %d Registry: %d", active_side, registry);
      registry++;
    }
    delay(500);
  }else{
    current_time = millis();
  }
}

//handles response from the backend. If the registration sequence 
//it will return the corresponding case. Should be inside modeSelect if
//registration mode is active. 
int registrationResponse(String command){
  if(command == "0"){
    status = "unregistered";
    isRegistered = false;
    //change case
  }if(command == "1"){
    status = "registered";
    isRegistered = true;
    //change case
  }
}