#include "analogReading.h"

void setup() 
{
  Serial.begin(115200);
  delay(500);
  initReading();
}

void loop() {
  loopReading();
}
