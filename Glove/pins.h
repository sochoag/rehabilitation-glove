#ifndef pins_h
#define pins_h
  const byte flexPins[] = {0,2,4,6,8}; // Sensores Flex
  const byte flexSize = sizeof(flexPins);

  const byte phalangePins[] = {1,3,5,7}; // Sensores Falanges
  const byte phalangeSize = sizeof(phalangePins);

  const byte selectorsPins[]={26,25,33,32};

  const byte selectorsSize =  sizeof(selectorsPins);

  const byte analogPin = 36;
#endif