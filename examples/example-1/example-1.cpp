#include "Cubeio.h"

Cubeio mycube(1,2,3,4);
char active_side;

void setup(){
  Serial.begin(9600);
}

void loop(){
  active_side = mycube.getActiveSide();
  Serial.println(active_side);

  delay(2000);
}
