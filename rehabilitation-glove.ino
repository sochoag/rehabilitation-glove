#include "variables.h"
#include "fingers.h"
#include "connections.h"

void setup() 
{
  Serial.begin(115200);
  delay(500);
  Serial.println("Setup");
  initWifi();
  initMQTT();
  initFingers();
}

void loop() 
{
  if(millis()-last > period)
  {
    last = millis();
    publishMQTT("glove/fingers/sens", fingersReading());
  }
  loopMQTT();
}
