#ifndef fingers_h
#define fingers_h

void initFlex()
{
  for (int i = 0; i < flexSize; i++)
  {
    pinMode(flexPins[i], INPUT);
    Serial.println("Pin " + String(flexPins[i]) + " como entrada analogica");
  }
}

String flexReading()
{
  int flexRead[flexSize];
  char buffer[60];
  for (int i = 0; i < flexSize; i++)
  {
    flexRead[i] = 0;
  }
  for (int i = 0; i < flexSize; i++)
  {
    flexRead[i] = map(analogRead(flexPins[i]), 0, 4095, 0, 100);
  }
  snprintf(buffer, sizeof(buffer), "{\"f1\":%d,\"f2\":%d,\"f3\":%d,\"f4\":%d,\"f5\":%d}", flexRead[0], flexRead[1], flexRead[2], flexRead[3], flexRead[4]);
  return buffer;
}
#endif