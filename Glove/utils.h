#ifndef UTILS_H
#define UTILS_H

int analogReadExpanded(int pin)
{
  for(int i = 0; i < selectorsSize; i++){
    bool bitVal = (pin >> i) & 1;
    digitalWrite(selectorsPins[i], bitVal);
  }
  return analogRead(analogPin);
}

void initUtils(){
  pinMode(analogPin, INPUT);
  for(byte i = 0; i < selectorsSize; i++){
    pinMode(selectorsPins[i], OUTPUT);
  }
}

#endif