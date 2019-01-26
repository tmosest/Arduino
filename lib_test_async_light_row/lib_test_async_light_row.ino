#include <AsyncLightRow.h>

AsyncLightRow asyncLightRow(0, 11, 500);
boolean buttonPressed = false;
int buttonPin = 12;

void setup() {
  pinMode(buttonPin, INPUT);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    buttonPressed = !buttonPressed;
  }
  if (buttonPressed) {
    asyncLightRow.stop();
  } else {
    asyncLightRow.start();
  }
  asyncLightRow.loop();
}
