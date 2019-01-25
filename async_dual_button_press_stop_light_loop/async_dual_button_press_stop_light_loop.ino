/**
 * CONSTANTS
 */
// LIGHTS
unsigned int LIGHTS_START = 0;
unsigned int LIGHTS_END = 11;
// BUTTONS
unsigned int BUTTON_ONE = 13;
unsigned int BUTTON_TWO = 12;
// VARIABLES
unsigned long lightSpeed = 500;
unsigned long buttonSpeed = 500;
unsigned long previousButtonMillis = 0;        // will store last time LED was updated
unsigned long previousLightMillis = 0;        // will store last time LED was updated
int previousLight = -1;
int currentLight = LIGHTS_START;
boolean forwards = true;
boolean shouldLoopLights = true;

void setup() {
  setupLights();
  setupButtons();
}

void setupLights() {
  for (int i = LIGHTS_START; i < LIGHTS_END; i++) {
    Serial.print("setup: pinMode(");
    Serial.print(i);
    Serial.print(", OUTPUT)\n");
    pinMode(i, OUTPUT);
  }
}

void setupButtons() {
  pinMode(BUTTON_ONE, INPUT);
  pinMode(BUTTON_TWO, INPUT);
}

void loop() {
  loopButtonInput();
  loopLights();
}

void loopButtonInput() {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousButtonMillis >= buttonSpeed) {
    // save the last time you blinked the LED
    previousButtonMillis = currentMillis;
    int buttonOnePressed = digitalRead(BUTTON_ONE) == HIGH;
    int buttonTwoPressed = digitalRead(BUTTON_TWO) == HIGH;
    if (buttonOnePressed || buttonTwoPressed) {
      shouldLoopLights = false;
      turnOffLights();
      for (int i = 0; i < 3; i++) {
        if (buttonOnePressed) {
          digitalWrite(LIGHTS_START, HIGH);
        }
        if (buttonTwoPressed) {
          digitalWrite(LIGHTS_END - 1, HIGH);
        }
        delay(lightSpeed);
        if (buttonOnePressed) {
          digitalWrite(LIGHTS_START, LOW);
        }
        if (buttonTwoPressed) {
          digitalWrite(LIGHTS_END - 1, LOW);
        }
        delay(lightSpeed);
      }
      shouldLoopLights = true;
    }
  }
}

void turnOffLights() {
  for (int i = LIGHTS_START; i < LIGHTS_END; i++) {
    digitalWrite(i, LOW);
  }
}

void loopLights() {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (shouldLoopLights && currentMillis - previousLightMillis >= lightSpeed) {
    // save the last time you blinked the LED
    previousLightMillis = currentMillis;
    if (previousLight != -1) {
      digitalWrite(previousLight, LOW);
    }
    digitalWrite(currentLight, HIGH);
    previousLight = currentLight;
    if (currentLight == LIGHTS_START) {
      forwards = true; 
    } else if (currentLight == LIGHTS_END - 1) {
      forwards = false;
    }
    if (forwards) {
      currentLight += 1;
    } else {
      currentLight -= 1;
    }
  }
}

