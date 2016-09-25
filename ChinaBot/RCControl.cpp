#include "RCControl.h"
#include "Arduino.h"


const int RCControl::ForwardControlPin = A0;
const int RCControl::SideControlPin = A1;
const int RCControl::YawPin = A2;

const int RCControl::mPWMAPIN = 3;
const int RCControl::mPWMBPIN = 11;
const int RCControl::mDIRAPIN = 12;
const int RCControl::mDIRBPIN = 13;
const int RCControl::DEADBAND = 50;

const unsigned long RCControl::MIN_DURATION = 1100;
const unsigned long RCControl::MAX_DURATION = 1900;

void RCControl::Setup()
{  
  pinMode(mPWMAPIN, OUTPUT);  //Set control pins to be outputs
  pinMode(mPWMBPIN, OUTPUT);
  pinMode(mDIRAPIN, OUTPUT);
  pinMode(mDIRBPIN, OUTPUT);

  player.Setup();
}

void RCControl::Detect()
{
  //Serial.println(pulseIn(ForwardControlPin,HIGH));
  mForwardPWM = map( pulseIn(ForwardControlPin,HIGH), 
                     (int)MIN_DURATION,
                     (int)MAX_DURATION,
                     -255,
                      255 );

  mSidePWM = map( pulseIn(SideControlPin,HIGH), 
                  (int)MIN_DURATION,
                  (int)MAX_DURATION,
                  -255,
                   255 );

  mSongSelect = map( pulseIn(YawPin,HIGH), 
                  (int)MIN_DURATION,
                  (int)MAX_DURATION,
                  -255,
                   255 );

}

void RCControl::Send()
{
  unsigned int left_dir, right_dir;

  if( (abs(mForwardPWM) < DEADBAND) 
      or (mForwardPWM < -1000) )
  {
    mForwardPWM = 0;
  }

  if( (abs(mSidePWM) < DEADBAND) 
      or (mSidePWM < -1000) )
  {
    mSidePWM = 0;
  }

  left_speed = 1.0*float(-mForwardPWM+mSidePWM);
  right_speed = 1.0*float(mForwardPWM+mSidePWM);


  left_dir  = (left_speed>0?HIGH:LOW);
  right_dir = (right_speed>0?LOW:HIGH);

  left_speed  = constrain(abs(left_speed),0,250);
  right_speed = constrain(abs(right_speed),0,250);

  Serial.print("LD: ");
  Serial.print(left_dir);
  Serial.print(" RD: ");
  Serial.print(right_dir);
  Serial.print(" LS: ");
  Serial.print(left_speed);
  Serial.print(" RS: ");
  Serial.println(right_speed);

  
  digitalWrite(mDIRAPIN, left_dir);
  digitalWrite(mDIRBPIN, right_dir);
  analogWrite(mPWMAPIN, left_speed);
  analogWrite(mPWMBPIN, right_speed);

}

void RCControl::Update()
{
  Detect();
  Send();
}
