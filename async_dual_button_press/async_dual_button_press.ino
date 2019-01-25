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
unsigned long previousMillis = 0;        // will store last time LED was updated
int previousLight = -1;
int currentLight = LIGHTS_START;
boolean forwards = true;

void setup() {
  pinMode(LIGHTS_START, OUTPUT);
  pinMode(LIGHTS_END - 1, OUTPUT);
  pinMode(BUTTON_ONE, INPUT);
  pinMode(BUTTON_TWO, INPUT);
}

void loop() {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= buttonSpeed) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    int buttonOnePressed = digitalRead(BUTTON_ONE) == HIGH;
    int buttonTwoPressed = digitalRead(BUTTON_TWO) == HIGH;

    if (buttonOnePressed || buttonTwoPressed) {
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
    }
  }
}

