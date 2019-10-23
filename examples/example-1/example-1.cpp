#include "Cubeio.h"
// #define PIXEL_COUNT 1
// #define PIXEL_PIN D1
// #define PIXEL_TYPE WS2812B

//Adafruit_NeoPixel externalLed = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

Cubeio mycube(D6, D1, A1,A2,A3);
char active_side;

void setup(){
  Serial.begin(9600);
  mycube.setThreshold(30);
  mycube.enableLedControl();
  mycube.setLedBrightness(50);
}

void loop(){
  active_side = mycube.getActiveSide();
  mycube.setLedColor(255,0,0);
  Serial.println(active_side);

  delay(1000);
  mycube.setLedColor(0,255,0);
  delay(1000);
  mycube.setLedColor(0,0,255);
  delay(1000);
}
