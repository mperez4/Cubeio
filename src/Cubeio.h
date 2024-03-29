#ifndef Cubeio_h
#define Cubeio_h

#include "Particle.h"
#include "a pplication.h"
#include "neopixel.h"

class Cubeio{
  public:
    Cubeio(const uint8_t switchPin, const uint8_t ledPin, const uint8_t xPin, const uint8_t yPin, const uint8_t zPin);
    uint8_t roll, pitch;
    char getActiveSide();
    bool buttonPressed();
    int
      x_value, y_value, z_value;
    int side[6] = {1, 2, 3, 4, 5, 6};
    int sides_array[6][2];
    void 
      readSensorData(int x, int y, int z),
      calculateRollPitch(),
      loadCalibrationValuesFromEEPROM(),
      getCalibrationResult(),
      setFrequency(int frequency),
      setThreshold(int threshold),
      setLedColor(int r, int g, int b),
      setLedBrightness(int brightness),
      publishOnChange(String eventName = "active_side"),
      enableLedControl(),
      attachButton(InterruptMode mode),
      detachButton(),
      disableLedControl();

  private:
    Adafruit_NeoPixel *externalLed;
    int 
      _switchPin, _ledPin, _xPin, _yPin, _zPin,
      _frequency, active_side, _prevside, _currentside;
    int _threshold = 20;
    int addr = 0;
    String payload;

    double 
      x_g_value, y_g_value, z_g_value;
    volatile int state = LOW;
    struct calibrationValues {
      int side;
      int pitch;
      int roll;
    }calibrationValues, valueSet;
    void interruptHandler();
};

#endif