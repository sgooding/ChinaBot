#include "BehaviourFunctions.h"
#include "Arduino.h"


bool Behaviour::mObstacleMap[] = {false, false, false};

bool Behaviour::check_timeout(State* state, unsigned long delta_ms)
{
  unsigned long delta = (millis() - state->time_start);
  return ( delta > delta_ms );
}

bool Behaviour::backup(State* state)
{
    if( check_timeout(state,BACKUP_DISTANCE) )
    {
     
      if( !mObstacleMap[0] ) // if left is clear, go left
      {
        Serial.println("Obstacle Clear On Left->Go Left");
        left();
      }
      else // otherwise, just turn right
      {
        Serial.println("Obstacle -> Go Right");
        right();
      }

      
      state->next_cmd = &turn;
      state->time_start = millis();
 
      return true;
    }
    return false;
}

bool Behaviour::turn(State* state)
{
    if( check_timeout(state, TURN_DISTANCE ) )
    {
      //stopped();
      Serial.println("Turn Complete->Detect Left");
      reset_blocked();
      state->next_cmd = &detect_left;
      state->time_start = millis();
      return true;
    }
    return false;
}

bool Behaviour::move_fwd(State* state)
{
  //Serial.println("In move_fwd");
  if( check_timeout(state, TRAVEL_DISTANCE ) )
  {
    Serial.println("mov_fwd: detect_left");
    //stopped();
      state->next_cmd = &detect_left;
      state->time_start = millis();
      return true;
  }
  return false;
}

bool Behaviour::choose_direction(State* state)
{
  Serial.println("choose");
    char o_map[] = {(mObstacleMap[0]?'x':'.'),(mObstacleMap[1]?'x':'.'),(mObstacleMap[2]?'x':'.'),0};
    Serial.println(o_map);
  if( mObstacleMap[0] || mObstacleMap[1] || mObstacleMap[2] )
  {  
    Serial.println("Obstacle Detected->Go Backward");
    stopped();
    backward();
    state->next_cmd = &backup;
    state->time_start = millis();
    
    return true;
  }
  else
  {
    Serial.println("Forward");
    reset_blocked();
    
    forward();
    state->next_cmd = &move_fwd;
    state->time_start = millis();
    
    return true;
  }
  
  return false;
}

bool Behaviour::detect_right(State* state)
{

  //Serial.print(millis());
  //Serial.print(" : ");
  //Serial.print(state->time_start);
  //Serial.println(SENSE_TIMEOUT);
  if( check_timeout(state, SENSE_TIMEOUT) )
  {
  
    unsigned int distance = sonar_fr.ping_cm();

    if(sonar_fr.check_timer())
    {
      mObstacleMap[2] = ( (distance > 0) && (distance < STANDOFF) );
    }
    else
    {
      Serial.println("right check failed");
      mObstacleMap[2] = false;
      //state->next_cmd = &detect_right;
      //state->time_start = millis();
    }
    //Serial.print("R: ");
    //Serial.println(distance);
    //Serial.print("Check Timer: " );
    //Serial.println(sonar_fr.check_timer());
    
    state->next_cmd = &choose_direction;
    state->time_start = millis();
    return true;
  }

  return false;
}

bool Behaviour::detect_center(State* state)
{
  // check blocked
  if( check_timeout(state, SENSE_TIMEOUT) )
  {
    
    int median = sonar_c.ping_median(10);
    unsigned int distance = sonar_c.convert_cm(median);

    if(sonar_c.check_timer())
    {
      mObstacleMap[1] = ( (distance > 0) && (distance < STANDOFF) );
    }
    else
    {
      Serial.println("center check failed");
      mObstacleMap[1] = false;
      //state->next_cmd = &detect_center;
      //state->time_start = millis();
      //return true;
    }
    //Serial.print("C: ");
    //Serial.println(distance);
    //Serial.print("Check Timer: " );
    //Serial.println(sonar_c.check_timer());
    
     
    state->next_cmd = &detect_right;
    state->time_start = millis();
    return true;
  }
  return false;
}

bool Behaviour::detect_left(State* state)
{
  if( check_timeout(state,SENSE_TIMEOUT) ) 
  {
    
    int median = sonar_fl.ping_median(10);
    unsigned int distance = sonar_fl.convert_cm(median);
    //Serial.print("Check Timer: " );
    //Serial.println(sonar_fl.check_timer());

    if(sonar_fl.check_timer())
    {
      mObstacleMap[0] = ( (distance > 0) && (distance < STANDOFF) );
    }
    else
    {
      mObstacleMap[0] = false;
      //Serial.println("left check failed");
      //state->next_cmd = &detect_left;
      //state->time_start = millis();
      //true;
    }
    ///Serial.print("L: ");
    //Serial.println(distance);
    // if blocked
    state->next_cmd = &detect_center;
    state->time_start = millis();
    return true;
  }
  return false;
}

void Behaviour::init_state(void)
{
  mCurrentCmd = &detect_left;
  mState.next_cmd = &detect_left;
  mState.time_start = millis();
}


void Behaviour::reset_blocked()
{
}

void Behaviour::update()
{
  if( (this->*mCurrentCmd)(&mState))
  {
    //Serial.println("Next Command");
    mCurrentCmd = mState.next_cmd;
  }
}

