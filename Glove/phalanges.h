#ifndef PHALANGES_H
#define PHALANGES_H

String phalangesReading() {
  String phalangesRead[phalangeSize];
  char buffer[70];
  for (byte i = 0; i < phalangeSize; i++) {
    int lecture = analogReadExpanded(phalangePins[i]);
    String value = "";
    switch (lecture) {
      case 0 ... 1600:
        value = "Proximal";
        break;
      case 1601 ... 2500:
        value = "Medial";
        break;
      case 2501 ... 3500:
        value = "Distal";
        break;
      default:
        value = "";
        break;
    }
    phalangesRead[i] = value;
  }
  snprintf(buffer, sizeof(buffer), "{\"r1\":\"%s\",\"r2\":\"%s\",\"r3\":\"%s\",\"r4\":\"%s\"}", phalangesRead[0], phalangesRead[1], phalangesRead[2], phalangesRead[3]);
  return buffer;
}

#endif