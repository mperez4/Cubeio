//sets calibration results from particle api.
//save new calibration values to EEPROM

#include "Cubeio.h"

Cubeio mycube(D6, D1, A1,A2,A3);
int setCalibration(String command);
int sides_array[6][2];
int num_sides = 6;

struct calibrationValues {
  int side;
  int _sides_array[6][2];
};

struct prvalues{
  int side;
  int pitch;
  int roll;
};

union{
  prvalues prvars;
}storedValues[6], getValues[6];

//prvalues getValues[6];

 int addr = 0;

void setup(){
  Serial.begin(9600);
  Particle.function("set_calibration", setCalibration);
}

void loop(){

}

int setCalibration(String command){
  if(command == "save"){
    EEPROM.put(addr, storedValues);
    return 1;
  }
  if(command == "results"){
    for(int i = 0; i < num_sides; i++){
      String payload = "";
      payload = String(mycube.side[i]) + "," + String(mycube.sides_array[i][1]) + "," + String(mycube.sides_array[i][0]);
      Serial.println(payload);
      delay(1000);
    }
    return 1;
  }
  if(command == "printstruct"){
    for(int i = 0; i < num_sides; i++){
      Serial.print(storedValues[i].prvars.side);
      Serial.print(", ");
      Serial.print(storedValues[i].prvars.roll);
      Serial.print(", ");
      Serial.println(storedValues[i].prvars.pitch);
    }
    return 1;
  }
  if(command == "print"){
    for(int i = 0; i < 6; i++){
      int mypitch = EEPROM.get(addr, getValues[i].prvars.pitch);
      int myroll = EEPROM.get(addr, getValues[i].prvars.roll);

      Serial.print(mypitch);
      Serial.print(", ");
      Serial.println(myroll);

    }
    return 1;
  }
  if(command == "update"){
    for(int i =0; i < num_sides; i++){
      mycube.sides_array[i][0] = EEPROM.get(addr,getValues[i].prvars.roll);
      mycube.sides_array[i][1] = EEPROM.get(addr,getValues[i].prvars.pitch);
    }
    return 1;
  }
  if(isdigit(command[0]) && command.toInt() > 0 && command.toInt() <= num_sides){
    mycube.getRollPitch();

    storedValues[command.toInt() - 1].prvars.side = command.toInt() - 1;
    storedValues[command.toInt() - 1].prvars.pitch = mycube.pitch;
    storedValues[command.toInt() - 1].prvars.roll = mycube.roll;

    Serial.println("Side: " + command + " Pitch: " + String(mycube.pitch) +
      "  Roll: " + String(mycube.roll));
    return command.toInt();
  }
  else{
    Serial.println("Please use a valid command!");
    return -1;
  }
}