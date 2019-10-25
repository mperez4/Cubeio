//sets calibration results from particle api.
//save new calibration values to EEPROM

#include "Cubeio.h"

Cubeio mycube(D6, D1, A1,A2,A3);
int setCalibration(String command);
int sides_array[6][2];


void setup(){
  Serial.begin(9600);
  Particle.function("set_calibration", setCalibration);
}

void loop(){

}

int setCalibration(String command){
  if(command == "save"){
    Serial.println("Saving results to EEPROM...");
  }
  if(command == "results"){
    for(int i = 0; i < 6; i++){
      String payload = "";
      payload = String(mycube.side[i]) + "," + String(sides_array[i][1]) + "," + String(sides_array[i][0]);
      Serial.println(payload);
      delay(1000);
    }
  }
  else{
    mycube.getRollPitch();
    sides_array[command.toInt()][0] = mycube.pitch;
    sides_array[command.toInt()][1] = mycube.roll;
    Serial.print(sides_array[command.toInt()][0]);
    Serial.print(", ");
    Serial.println(sides_array[command.toInt()][1]);
  }
  return 1;
}