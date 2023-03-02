#include "variables.h"
#include "pins.h"
#include "fingers.h"
#include "connections.h"
#include "touch.h"
#include "phalanges.h"

void setup() 
{
  Serial.begin(115200);
  delay(500);
  Serial.println("Setup");
  // initWifi();
  // initMQTT();
  // initFlex();
  // initTouch();
  initPhalanges();
}

void loop() 
{
  phalangesReading();
  // if(millis()-last > period)
  // {
  //   last = millis();
  //   publishMQTT("glove/fingers/sens", flexReading());
  // }
  // loopMQTT();
  // touchFlagFunc();
}
