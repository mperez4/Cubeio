//sets calibration results from particle api.
//save new calibration values to EEPROM

#include "Cubeio.h"

Cubeio mycube(D6, D1, A1,A2,A3);
int setCalibration(String command);
int sides_array[6][2];
int num_sides = 6;

void setup(){
  Serial.begin(9600);
  Particle.function("set_calibration", setCalibration);
}

void loop(){

}

int setCalibration(String command){
  if(command == "save"){
    Serial.println("Saving results to EEPROM...");
    return 1;
  }
  if(command == "results"){
    for(int i = 0; i < 6; i++){
      String payload = "";
      payload = String(mycube.side[i]) + "," + String(sides_array[i][1]) + "," + String(sides_array[i][0]);
      Serial.println(payload);
      delay(1000);
    }
    return 1;
  }
  if(isdigit(command[0]) && command.toInt() > 0 && command.toInt() <= num_sides){
    mycube.getRollPitch();
    sides_array[command.toInt() - 1][0] = mycube.pitch;
    sides_array[command.toInt() - 1][1] = mycube.roll;
    Serial.println("Side: " + command + " Pitch: " + String(mycube.pitch) +
      "  Roll: " + String(mycube.roll));
    return command.toInt();
  }
  else{
    Serial.println("Please use a valid command!");
    return -1;
  }
}