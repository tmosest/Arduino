#include "Arduino.h"
#include "AsyncButtonRow.h"

AsyncButtonRow::AsyncButtonRow(unsigned int start, unsigned int end, unsigned int speed) {
  _start = start;
  _end = end;
  _speed = speed;
  _states = new bool[buttonCount()];
  for (int i = _start; i <= _end; i++) {
    pinMode(i, INPUT);
  }
}

bool* AsyncButtonRow::loop() {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - _previousMillis >= _speed) {
    _previousMillis = currentMillis;
    for (int i = _start; i <= _end; i++) {
      _states[i - _start] = (digitalRead(i) == HIGH);
    }
    return _states;
  }

  for (int i = _start; i <= _end; i++) {
    _states[i - _start] = false;
  }
  return _states;
}

void AsyncButtonRow::updateSpeed(int speed) {
  _speed = speed;
}

int AsyncButtonRow::buttonCount() {
  return _end - _start + 1;
}

