/**
 * CONSTANTS
 */
// LIGHTS
unsigned int LIGHTS_START = 0;
unsigned int LIGHTS_END = 11;
// VARIABLES
unsigned long lightSpeed = 500;
unsigned long previousMillis = 0;        // will store last time LED was updated
int previousLight = -1;
int currentLight = LIGHTS_START;
boolean forwards = true;

void setup() {
  // put your setup code here, to run once:
  Serial.println("setup: start");
  for (int i = LIGHTS_START; i < LIGHTS_END; i++) {
    Serial.print("setup: pinMode(");
    Serial.print(i);
    Serial.print(", OUTPUT)\n");
    pinMode(i, OUTPUT);
  }
  Serial.println("setup: end");
}

void loop() {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= lightSpeed) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

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

