#include "Particle.h"
#include "Cubeio.h"
#include "math.h"
#define PIXEL_TYPE WS2812B


Cubeio::Cubeio(const uint8_t switchPin, const uint8_t ledPin, const uint8_t xPin, const uint8_t yPin, const uint8_t zPin)
{
  _switchPin = switchPin;
  _ledPin = ledPin;
  _xPin = xPin;
  _yPin = yPin;
  _zPin = zPin;

  pinMode(_switchPin, INPUT_PULLUP);
  pinMode(D7, OUTPUT);

  externalLed = new Adafruit_NeoPixel(1,1, PIXEL_TYPE);
  externalLed->begin();
  loadCalibrationValuesFromEEPROM();
}

char Cubeio::getActiveSide(){
  calculateRollPitch();
  for (int i = 0; i < 6; ++i){
    if (roll > sides_array[i][1] - _threshold && roll < sides_array[i][1] + _threshold &&
        pitch > sides_array[i][0] - _threshold && pitch < sides_array[i][0] + _threshold){
        active_side = side[i];
        //Serial.printlnf("Pitch: %d, %d Roll: %d, %d Side: %d",pitch, sides_array[i][0], roll, sides_array[i][1], active_side);
    }
  }
  return active_side;
}

void Cubeio::publishOnChange(String eventName){
  _currentside = getActiveSide();
  if(_prevside != _currentside){
    Particle.publish(eventName, String(_currentside));
    delay(1000);//so that it doesnt spam the particle api
  }
  _prevside = _currentside;
}

void Cubeio::getCalibrationResult(){
  for(int i = 0; i < 6; i++){
    Serial.printlnf("Side: %d Pitch: %d Roll: %d", side[i], sides_array[i][0], sides_array[i][1]);
  }
}

void Cubeio::loadCalibrationValuesFromEEPROM(){
  for(int i =0; i < 6; i++){
    EEPROM.get(addr + i*sizeof(calibrationValues), valueSet);
    sides_array[i][0] = valueSet.pitch;
    sides_array[i][1] = valueSet.roll;
  }
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

void Cubeio::interruptHandler(){
  state = !state;
  digitalWrite(D7, state);
}

void Cubeio::attachButton(InterruptMode _mode){
  attachInterrupt(_switchPin, &Cubeio::interruptHandler, this, _mode);
}

void Cubeio::detachButton(){
  detachInterrupt(_switchPin);
}

bool Cubeio::buttonPressed(){
  if(!state){
    return false;
  }
  else return true;
}

void Cubeio::readSensorData(int x, int y, int z){
  x_value = analogRead(x);
  y_value = analogRead(y);
  z_value = analogRead(z);
}

void Cubeio::calculateRollPitch(){
  readSensorData(_xPin, _yPin, _zPin);

  x_g_value = ((((double)(x_value * 3.3) / 4095) - 1.65) / 0.330);
  y_g_value = ((((double)(y_value * 3.3) / 4095) - 1.65) / 0.330);
  z_g_value = ((((double)(z_value * 3.3) / 4095) - 1.80) / 0.330);

  roll = (((atan2(y_g_value, z_g_value) * 180) / 3.14) + 180);
  pitch = (((atan2(z_g_value, x_g_value) * 180) / 3.14) + 180);
}
