#ifndef fingers_h
#define fingers_h

  #include "pins.h"

  void initFingers()
  {
    for(int i=0; i<sizePines; i++)
    {
      pinMode(AnalogPins[i], INPUT);
      Serial.println("Pin "+String(AnalogPins[i])+" como entrada analogica");
    }
  }

  String fingersReading()
  {
    int read[5] = {0,0,0,0,0};
    char buffer[60];
    for(int i=0; i<sizePines; i++)
    {
      read[i] = map(analogRead(AnalogPins[i]), 0, 4095, 0, 100);
    }
    snprintf(buffer,sizeof(buffer),"{\"f1\":%d,\"f2\":%d,\"f3\":%d,\"f4\":%d,\"f5\":%d}", read[0], read[1], read[2], read[3], read[4]);
    return buffer;
  }
#endif