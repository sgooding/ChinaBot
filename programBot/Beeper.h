#ifndef BEEPER_H
#define BEEPER_H

#include <arduino.h>

class Beeper
{
  public:
  static void beep(unsigned char delayms, unsigned char tone = 20)
  {
    if(!beep_enabled)
    {
      pinMode(9,OUTPUT); 
      beep_enabled = true;
    }
    analogWrite(9,tone);
    delay(delayms);
    analogWrite(9,0);
  }
  static void confirm()
  {
    beep(100);
    beep(100,100);
    beep(100,20);
    beep(500,100);
    delay(1000);
  }
  static void complete()
  {
    beep(100,100);
    beep(100,10);
  }
  private:
  static bool beep_enabled;
};
#endif
