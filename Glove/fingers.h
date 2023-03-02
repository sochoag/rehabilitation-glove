#ifndef fingers_h
#define fingers_h

  void initFlex()
  {
    for(int i=0; i<flexSize; i++)
    {
      pinMode(flexPins[i], INPUT);
      Serial.println("Pin "+String(flexPins[i])+" como entrada analogica");
    }
  }

  String flexReading()
  {
    int read[5] = {0,0,0,0,0};
    char buffer[60];
    for(int i=0; i<flexSize; i++)
    {
      read[i] = map(analogRead(flexPins[i]), 0, 4095, 0, 100);
    }
    snprintf(buffer,sizeof(buffer),"{\"f1\":%d,\"f2\":%d,\"f3\":%d,\"f4\":%d,\"f5\":%d}", read[0], read[1], read[2], read[3], read[4]);
    return buffer;
  }
#endif