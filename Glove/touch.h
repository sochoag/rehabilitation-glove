#ifndef touch_h
#define touch_h

void reportTouch(){
  static unsigned long touchLastTime = 0;
  if(millis() - touchLastTime > 1500)
  {
    touchLastTime = millis();
    Serial.println("Touch detected!");
    touchFlag = true;
    touchReadValue = touchRead(touchPin);
  }
}

void touchFlagFunc()
{
  if(touchFlag){
  touchFlag = false;
    char bufferTouch[15];
    snprintf(bufferTouch,sizeof(bufferTouch),"{\"t1\":%d}", touchReadValue);
    Serial.println("Touch detected!");
    publishMQTT("glove/fingers/sens",bufferTouch);
  }
}
void initTouch(){
  touchAttachInterrupt(touchPin, reportTouch, threshold);
}

#endif