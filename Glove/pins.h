#ifndef pins_h
#define pins_h
  const byte flexPins[] = {36,39,34,35,32}; // Sensores Flex
  const byte flexSize = sizeof(flexPins);

  // const byte phalangePins[] = {33,25,26,27,15}; // Sensores Falanges
  const byte phalangePins[] = {15}; // Sensores Falanges
  const byte phalangeSize = sizeof(phalangePins);

  const byte touchPin = 4; //Touch
#endif