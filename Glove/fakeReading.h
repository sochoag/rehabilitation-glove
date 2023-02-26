#ifndef fake_h
#define fake_h
String loopFReading()
{
  char buffer[46];
  snprintf(buffer, sizeof(buffer), "{\"f1\":%d,\"f2\":%d,\"f3\":%d,\"f4\":%d,\"f5\":%d,\"t1\":%d}", random(1,100), random(1,100),random(1,100),random(1,100),random(1,100),random(1,100));
  return buffer;
}
#endif