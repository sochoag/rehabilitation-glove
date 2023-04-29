#include "pins.h"
#include "variables.h"
#include "secrets.h"
#include "oled.h"
#include "utils.h"
#include "connections.h"
#include "fingers.h"
#include "phalanges.h"

void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println("Setup");
  oledSetup();
  connect();
  initUtils();
  getTime();
}

void loop()
{
  String flexSensors = flexReading();
  String phalanges = phalangesReading();
  if (millis() - last > period)
  {
    last = millis();
    publishMQTT("glove/fingers/flex", flexSensors);
    publishMQTT("glove/fingers/touch", phalanges);
  }
  if (millis() - last2 > 30000)
  {
    last2 = millis();
    getTime();
  }
  loopOled();
  loopMQTT();
}
