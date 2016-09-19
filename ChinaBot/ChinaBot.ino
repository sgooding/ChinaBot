/*
 * ChinaBot
 * -driver for my little robot
 */
#include "SonarFunctions.h"
#include "MotorFunctions.h"

typedef bool(*FUNC)(void);
FUNC gCurrentCmd = NULL;
FUNC gNextCmd = NULL;

bool gLeftBlocked = false;
bool gCenterBlocked = false;
bool gRightBlocked = false;
unsigned long gMoveStart = 0;
unsigned long gPingTime = 0;

bool gMoveBackComplete = false;
bool gTurnComplete = false;

#define TRAVEL_DISTANCE  500
#define STANDOFF 50

bool detect_left();

bool backup_turn()
{
    //Serial.println("BKUP-TURN");

  if(!gMoveBackComplete)
  {
    if( (millis() - gMoveStart) < TRAVEL_DISTANCE )
    {
       // send backward command
       //backward();
       //return false;
    }
    else
    {
      // send backward command stop
      gMoveBackComplete = true;
      gTurnComplete = false;
      gMoveStart = millis();
      if( gLeftBlocked )
      {
        right();
        //Serial.println("right");
      }
      else if ( gRightBlocked )
      {
        left();
        //Serial.println("left");
      }
      else
      {
        right();
        //Serial.println("center");
      }
      ///      delay(500);

    }
  }

  if(!gTurnComplete)
  {
    if( (millis() - gMoveStart) < TRAVEL_DISTANCE )
    {
      // send turn command
      //return false;
    }
    else
    {
      Serial.println("turn comple");
      gTurnComplete = true;
      gNextCmd = &detect_left;
      stopped();
      return true;
    }
  }

return false;
}

bool move_fwd()
{
  if( (millis() - gMoveStart) < TRAVEL_DISTANCE )
  {
    // send fwd command
  }
  else
  {
      gNextCmd = &detect_left;
      return true;
  }
  return false;
}

void reset_blocked()
{
    gCenterBlocked = false;
    gLeftBlocked = false;
    gRightBlocked = false;
}

bool choose_direction()
{
  if( gCenterBlocked || gLeftBlocked || gRightBlocked )
  {
    
    reset_blocked();
    
    gNextCmd = &backup_turn;
    gMoveStart = millis();
    gMoveBackComplete = false;
    backward();
    return true;
  }
  else
  {
    reset_blocked();
    
    gNextCmd = &move_fwd;
    gMoveStart = millis();
    forward();
    return true;
  }
  return false;
}

bool detect_right()
{


  if( (millis() - gPingTime) > 50 )
  {
  
    unsigned int distance = sonar_fr.ping_cm();
  
    if( (distance > 0) && (distance < STANDOFF) )
    {
      gRightBlocked = true;
    }
    else 
    {
      gRightBlocked = false;
    }
  
    gNextCmd = &choose_direction;
    gPingTime = millis();
    return true;
  }

  return false;
}

bool detect_center()
{
  // check blocked

  if( (millis() - gPingTime) > 50 )
  {

    unsigned int distance = sonar_c.ping_cm();
    if( (distance > 0) && (distance < STANDOFF) )
    {
      gCenterBlocked = true;
    }
    else 
    {
      gCenterBlocked = false;
    }
  
    gNextCmd = &detect_right;
    gPingTime = millis();
    return true;
  }
  return false;
}

bool detect_left()
{
  // check blocked
  //stopped();
  
  if( (millis() - gPingTime) > 50 )
  {
   
    unsigned int distance = sonar_fl.ping_cm();
  
    if( (distance > 0) && (distance < STANDOFF) )
    {
      gLeftBlocked = true;
    }
    else
    {
      gLeftBlocked = false;
    }
  
    // if blocked
    gNextCmd = &detect_center;
    gPingTime = millis();
    return true;
  }
  return false;
}

void setup() {
  // put your setup code here, to run once:

  gCurrentCmd = &detect_left;
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  setup_motors();
  stopped();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(gCurrentCmd())
  {
    gCurrentCmd = gNextCmd;
  }
}
