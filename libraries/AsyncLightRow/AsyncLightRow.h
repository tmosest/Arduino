#include "Arduino.h"

#ifndef AsyncLightRow_h
#define AsyncLightRow_h

class AsyncLightRow {
 public:
  AsyncLightRow(unsigned int start, unsigned int end, unsigned int speed);
  void loop();
 private:
  unsigned int _start;
  unsigned int _end;
  unsigned int _speed;
  unsigned int _previousMillis;
  unsigned int _currentLight;
  unsigned int _prevLight;
  bool _forwards;
};

#endif