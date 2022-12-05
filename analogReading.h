#ifndef reading_h
#define reading_h

  #include "pins.h"

  void initReading()
  {
    for(int i=0; i<sizePines; i++)
    {
      pinMode(AnalogPins[i], INPUT);
      Serial.println("Pin "+String(AnalogPins[i])+" como entrada analogica");
    }
  }

  void loopReading()
  {
    for(int i=0; i<sizePines; i++)
    {
      int reading = analogRead(AnalogPins[i]);
      Serial.print(String(reading)+"\t");
    }
    Serial.println();
  }
#endif