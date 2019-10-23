#include "Particle.h"
#include "Cubeio.h"
#include "math.h"
#define PIXEL_TYPE WS2812B


Cubeio::Cubeio(const byte switchPin, const byte ledPin, const byte xPin, const byte yPin, const byte zPin)
{
  _switchPin = switchPin;
  _ledPin = ledPin;
  _xPin = xPin;
  _yPin = yPin;
  _zPin = zPin;
  pinMode(_switchPin, INPUT);
  externalLed = new Adafruit_NeoPixel(1,1, PIXEL_TYPE);
  externalLed->begin();

}

char Cubeio::getActiveSide(){
  readData(_xPin, _yPin, _zPin);

  x_g_value = ((((double)(x_value * 3.3) / 4095) - 1.65) / 0.330);
  y_g_value = ((((double)(y_value * 3.3) / 4095) - 1.65) / 0.330);
  z_g_value = ((((double)(z_value * 3.3) / 4095) - 1.80) / 0.330);

  roll = (((atan2(y_g_value, z_g_value) * 180) / 3.14) + 180);
  pitch = (((atan2(z_g_value, x_g_value) * 180) / 3.14) + 180);
  Serial.print(roll);
  Serial.print("    ");
  Serial.println(pitch);

  for (int i = 0; i < 6; ++i){
    if (roll > sides_array[i][0] - _threshold && roll < sides_array[i][0] + _threshold &&
        pitch > sides_array[i][1] - _threshold && pitch < sides_array[i][1] + _threshold){
        active_side = side[i];
    }
  }
  Serial.println(active_side);
  return active_side;
}

String Cubeio::getCalibrationResult(){
  for(int i = 0; i < 6; i++){
    payload = String(side[i]) + "," + String(sides_array[i][1]) + "," + String(sides_array[i][0]);
    Particle.publish("log_calibration_value", payload, PUBLIC);
    delay(1000);
  }
  return payload;
}

void Cubeio::setLedColor(int r, int g, int b){
  RGB.color(r,g,b);
  externalLed->setPixelColor(0, externalLed->Color(r, g , b));
  externalLed->show();
}

void Cubeio::setLedBrightness(int brightness){
  RGB.brightness(brightness);
  externalLed->setBrightness(brightness);
}

void Cubeio::setFrequency(int frequency){
  _frequency = frequency;
}

void Cubeio::setThreshold(int threshold){
  _threshold = threshold;
}

void Cubeio::enableLedControl(){
  RGB.control(true);
}

void Cubeio::disableLedControl(){
  RGB.control(false);
}

void Cubeio::readData(int x, int y, int z){
    x_value = analogRead(x);
    y_value = analogRead(y);
    z_value = analogRead(z);
}