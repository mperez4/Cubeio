//sets calibration results from particle api.
//save new calibration values to EEPROM

#include "Cubeio.h"

Cubeio mycube(D6, D1, A1,A2,A3);
int setCalibration(String command);
int num_sides = 6;


struct calibrationValues{
  int side;
  int pitch;
  int roll;
} storedValues[6], valueSet;
 
 int addr = 0;
int active_side;

void setup(){
  Serial.begin(9600);
  Particle.function("set_calibration", setCalibration);
  mycube.setThreshold(20);
}

void loop(){

}

int setCalibration(String command){
  if(command == "save"){
    //saves local values into the EEPROM address
    EEPROM.put(addr, storedValues);
    Serial.println("Saved calibration values to EEPROM");
    return 1;
  }
  if(command == "update"){
    //saves the values from the EEPROM into the cube object.
    //The values are applied by default on reset
    for(int i =0; i < num_sides; i++){
      EEPROM.get(addr + i*sizeof(calibrationValues), valueSet);
      mycube.sides_array[i][0] = valueSet.pitch;
      mycube.sides_array[i][1] = valueSet.roll;
    }
    Serial.println("Updated cube's roll and pitch values from EEPROM");
    return 1;
  }
  if(command == "printEEPROM"){
    //prints the calibration values from the EEPROM
    Serial.println("Calibration values stored in EEPROM:");
    for(int i = 0; i < 6; i++){
      EEPROM.get(addr + i*sizeof(calibrationValues), valueSet);
      Serial.printlnf("%d: %d, %d, %d", i, valueSet.side, valueSet.pitch, valueSet.roll);
    }
    return 1;
  }
    if(command == "printCube"){
    //prints the calibration numbers that the cube obj is using
    Serial.println("Calibration values stored in Cube:");
    for(int i = 0; i < num_sides; i++){
      Serial.printlnf("Side: %d Pitch: %d Roll: %d", mycube.side[i], mycube.sides_array[i][0], mycube.sides_array[i][1]);
    }
    return 1;
  }
  if(isdigit(command[0]) && command.toInt() > 0 && command.toInt() <= num_sides){
    mycube.getRollPitch();
    //stores the values locally to RAM
    storedValues[command.toInt() - 1].side = command.toInt();
    storedValues[command.toInt() - 1].pitch = mycube.pitch;
    storedValues[command.toInt() - 1].roll = mycube.roll;
    Serial.printlnf("Side: %d Pitch: %d Roll: %d", command.toInt(), mycube.pitch, mycube.roll);
 
    return command.toInt();
  }
  else{
    Serial.println("Please use a valid command!");
    return -1;
  }
}