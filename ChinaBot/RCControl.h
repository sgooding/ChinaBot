#ifndef RCCONTROL_H
#define RCCONTROL_H

#include "SongPlayer.h"

class RCControl
{
  public:
  void Setup();
  void Update();


  private:

  void Send();
  void Detect();
  void Mix();

  static const int mPWMAPIN; //PWM control for motor outputs 1 and 2 is on digital pin 3
  static const int mPWMBPIN; //PWM control for motor outputs 3 and 4 is on digital pin 11
  static const int mDIRAPIN; //direction control for motor outputs 1 and 2 is on digital pin 12
  static const int mDIRBPIN; //direction control for motor outputs 3 and 4 is on digital pin 13

  static const int ForwardControlPin;
  static const int SideControlPin;
  static const int YawPin;
  static const unsigned long MIN_DURATION;
  static const unsigned long MAX_DURATION;
  static const int DEADBAND;

  int mForwardPWM;
  int mSidePWM;
  int mSongSelect;

  float left_speed;
  float right_speed;

  SongPlayer player;

};
#endif

