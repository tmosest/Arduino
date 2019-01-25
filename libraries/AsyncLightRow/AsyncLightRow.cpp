#include "Arduino.h"
#include "AsyncLightRow.h"

AsyncLightRow::AsyncLightRow(unsigned int start, unsigned int end, unsigned int speed) {
  _start = start;
  _end = end;
  _speed = speed;
  _forwards = true;
  _prevLight = _start;
  _currentLight = _start;
  _previousMillis = 0;
  for (int i = start; i < end; i++) {
    pinMode(i, OUTPUT);
  }
}

void AsyncLightRow::loop() {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - _previousMillis >= _speed) {
    // save the last time you blinked the LED
    _previousMillis = currentMillis;
    digitalWrite(_prevLight, LOW);
    digitalWrite(_currentLight, HIGH);
    _prevLight = _currentLight;
    if (_currentLight == _start) {
      _forwards = true;
    } else if (_currentLight == _end - 1) {
      _forwards = false;
    }
    if (_forwards) {
      _currentLight += 1;
    } else {
      _currentLight -= 1;
    }
  }
}