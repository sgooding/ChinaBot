#ifndef BEHAVIOUR_FUNCTIONS_H
#define BEHAVIOUR_FUNCTIONS_H

#include "SonarFunctions.h"
#include "MotorFunctions.h"

#define TURN_DISTANCE  300
#define TRAVEL_DISTANCE  100
#define BACKUP_DISTANCE 200
#define STANDOFF 50
#define SENSE_TIMEOUT 1

class Behaviour
{
public:

  struct State
  {
    bool (Behaviour::*next_cmd)(State*);
    unsigned long time_start;
  };

  typedef bool(Behaviour::*FUNC)(State*);


  static bool mObstacleMap[];

  bool check_timeout(State* state, unsigned long delta_ms);

  bool backup(State* state);
 
  bool turn(State* state);
 
  bool move_fwd(State* state);
 
  bool choose_direction(State* state);
   
  bool detect_right(State* state);
 
  bool detect_center(State* state);
  
  bool detect_left(State* state);
  
  State mState;

  FUNC mCurrentCmd;

  void init_state(void);
 
  void reset_blocked();

  void update();

}; 



#endif
