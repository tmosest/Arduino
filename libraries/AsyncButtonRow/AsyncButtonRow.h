#include "Arduino.h"

#ifndef AsyncButtonRow_h
#define AsyncButtonRow_h

class AsyncButtonRow {
  public:
    AsyncButtonRow(unsigned int start, unsigned int end, unsigned int speed);
    bool* loop();
    void updateSpeed(int speed);
  private:
    bool* _states;
    unsigned int _start;
    unsigned int _end;
    unsigned int _speed;
    unsigned long _previousMillis;
};

#endif
