#include "Cubeio.h"

Cubeio mycube(D6, D1, A1,A2,A3);

void setup(){
  Serial.begin(9600);
}

void loop(){
  mycube.publishOnChange("active_side");
}

