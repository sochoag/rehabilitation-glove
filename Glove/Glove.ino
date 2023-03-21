#include "variables.h"
#include "secrets.h"
#include "pins.h"
#include "utils.h"
#include "connections.h"
#include "fingers.h"
#include "phalanges.h"

void setup() 
{
  Serial.begin(115200);
  delay(500);
  Serial.println("Setup");
  connect();
  initUtils();
  // initFlex();
  // initPhalanges();
}

void loop() 
{
  String flexSensors = flexReading();
  String phalanges = phalangesReading();
  if(millis()-last > period)
  {
    last = millis();
    publishMQTT("glove/fingers/flex", flexSensors);
    publishMQTT("glove/fingers/touch", phalanges);
  }
  loopMQTT();
}
