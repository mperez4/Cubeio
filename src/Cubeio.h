#ifndef Cubeio_h
#define Cubeio_h

#include "Particle.h"
#include "application.h"

class Cubeio{
  public:
    Cubeio(const byte switchPin, const byte xPin, const byte yPin, const byte zPin);
    char getActiveSide();
    int getPosition();
    String getCalibrationResult();
    
    void 
      setFrequency(int frequency),
      setThreshold(int threshold),
      setLedColor(int r, int g, int b),
      setLedBrightness(int brightness);

  private:
    int _switchPin, _ledPin, _xPin, _yPin, _zPin;
    int x_value, y_value, z_value;
    int _threshold, _frequency;
    int active_side;
    int sides_array[6][2] = {{0, 90}, {0, 0}, {180, 270}, {0, 180}, {90, 90}, {270, 90}};
    int side[6] = {1, 2, 3, 4, 5, 6};
    String payload;

    double x_g_value, y_g_value, z_g_value;
    double roll, pitch;
    void readData(int x, int y, int z);
    void calibrate();
};

#endif