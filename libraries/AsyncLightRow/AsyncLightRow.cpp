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
  for (int i = _start; i <= _end; i++) {
    pinMode(i, OUTPUT);
  }
  this->start();
}

void AsyncLightRow::loop() {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (_toLoop && currentMillis - _previousMillis >= _speed) {
    // save the last time you blinked the LED
    _previousMillis = currentMillis;
    digitalWrite(_prevLight, LOW);
    digitalWrite(_currentLight, HIGH);
    _prevLight = _currentLight;
    if (_currentLight == _start) {
      _forwards = true;
    } else if (_currentLight == _end) {
      _forwards = false;
    }
    if (_forwards) {
      _currentLight += 1;
    } else {
      _currentLight -= 1;
    }
  }
}

void AsyncLightRow::start() {
  _toLoop = true;
}

void AsyncLightRow::startRandom() {
  _currentLight = rand() % (_end) + _start;
  _prevLight = _currentLight;
  _forwards = (rand() % 1) == 0;
  start();
}


void AsyncLightRow::stop() {
  _toLoop = false;
}

void AsyncLightRow::turnOffLights() {
  for (int i = _start; i <= _end; i++) {
    digitalWrite(_prevLight, LOW);
  }
}

void AsyncLightRow::updateSpeed(int speed) {
  _speed = speed;
}

void AsyncLightRow::blinkLights(int lights[], int n, int times) {
  for (int t = 0; t < times; t++) {
    for (int i = 0; i < n; i++) {
      if (lights[i] >= _start && lights[i] <= _end) {
        digitalWrite(lights[i], HIGH);
      }
    }
    delay(_speed);
    for (int i = 0; i < n; i++) {
      if (lights[i] >= _start && lights[i] <= _end) {
        digitalWrite(lights[i], LOW);
      }
    }
    delay(_speed);
  }
}

unsigned int AsyncLightRow::getStartingLightIndex() {
  return _start;
}

unsigned int AsyncLightRow::getEndingLightIndex() {
  return _end;
}

unsigned int AsyncLightRow::getCurrentLight() {
  return _prevLight;
}

