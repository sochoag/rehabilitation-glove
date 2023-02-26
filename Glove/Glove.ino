#include "variables.h"
#include "fingers.h"
#include "connections.h"
#include "touch.h"

void setup() 
{
  Serial.begin(115200);
  delay(500);
  Serial.println("Setup");
  initWifi();
  initMQTT();
  initFingers();
  initTouch();
  Serial.println("ESP32 Touch Test");
}

void loop() 
{
  if(millis()-last > period)
  {
    last = millis();
    publishMQTT("glove/fingers/sens", fingersReading());
  }
  loopMQTT();
  touchFlagFunc();
}
