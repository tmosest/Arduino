#include <AsyncButtonRow.h>
#include <AsyncLightRow.h>

AsyncLightRow asyncLightRow(0, 11, 500);
AsyncButtonRow asyncButtonRow(12, 14, 500);

boolean buttonPressed = false;
int lightSpeed = 500;

void setup() {}

void loop() {
  bool* asyncButtonResult = asyncButtonRow.loop();
  if (asyncButtonResult[0] && asyncButtonResult[1]) {
    lightSpeed -= 50;
    if (lightSpeed <= 0) {
      lightSpeed = 500;
    }
    asyncLightRow.updateSpeed(lightSpeed);
  } else if (asyncButtonResult[0]) {
    asyncLightRow.stop();
  } else if (asyncButtonResult[1]) {
    asyncLightRow.start();
  }
  asyncLightRow.loop();
}

