#include <AsyncLightRow.h>

AsyncLightRow asyncLightRow(0, 11, 500);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  asyncLightRow.loop();
}
