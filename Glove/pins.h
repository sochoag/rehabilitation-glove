#ifndef pins_h
#define pins_h
  const byte flexPins[] = {0,2,3,6,8}; // Sensores Flex
  const byte flexSize = sizeof(flexPins);

  const byte phalangePins[] = {1,2,3,4}; // Sensores Falanges
  const byte phalangeSize = sizeof(phalangePins);

  const byte selectorsPins[]={32,33,25,26};
  const byte selectorsSize =  sizeof(selectorsPins);

  const byte analogPin = 36;
#endif