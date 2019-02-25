#include "Arduino.h"

#ifndef AsyncLightRow_h
#define AsyncLightRow_h

class AsyncLightRow {
 public:
  AsyncLightRow(unsigned int start, unsigned int end, unsigned int speed);
  void loop();
  void start();
  void startRandom();
  void stop();
  void turnOffLights();
  void updateSpeed(int speed);
  void blinkLights(int lights[], int n, int times);
  unsigned int getStartingLightIndex();
  unsigned int getEndingLightIndex();
  unsigned int getCurrentLight();
 private:
  unsigned int _start;
  unsigned int _end;
  unsigned int _speed;
  unsigned long _previousMillis;
  unsigned int _currentLight;
  unsigned int _prevLight;
  bool _forwards;
  bool _toLoop;
};

#endif