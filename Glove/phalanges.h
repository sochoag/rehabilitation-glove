#ifndef PHALANGES_H
#define PHALANGES_H

void initPhalanges()
  {
    for(int i=0; i<phalangeSize; i++)
    {
      pinMode(phalangePins[i], INPUT);
      Serial.println("Pin "+String(phalangePins[i])+" como entrada analogica");
    }
  }

void phalangesReading()
  {
    String read[phalangeSize];
    // char buffer[60];
    for(int i=0; i<phalangeSize; i++)
    {
      int lecture = analogRead(phalangePins[i]);
      String valor = "";
      switch (lecture){
        case 0 ... 1600:
          valor = "Proximal";
          break;
        case 1601 ... 2500:
          valor = "Media";
          break;
        case 2501 ... 3500:
          valor = "Distal";
          break;
        default:
          break;
      }
      read[i] = valor;
      Serial.println(read[i]);
    }
    // snprintf(buffer,sizeof(buffer),"{\"f1\":%d,\"f2\":%d,\"f3\":%d,\"f4\":%d,\"f5\":%d}", read[0], read[1], read[2], read[3], read[4]);
    // return buffer;
  }

#endif