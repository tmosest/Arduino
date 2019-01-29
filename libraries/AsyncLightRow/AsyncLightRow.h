#include "Arduino.h"

#ifndef AsyncLightRow_h
#define AsyncLightRow_h

class AsyncLightRow {
 public:
  AsyncLightRow(unsigned int start, unsigned int end, unsigned int speed);
  void loop();
  void start();
  void stop();
  void updateSpeed(int speed);
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