
/*
 * ChinaBot
 * -driver for my little robot
 */

//#include "MotorFunctions.h"
#include "BehaviourFunctions.h"
#include "RCControl.h"

Behaviour behaviour;
RCControl rc;

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  setup_motors();
  stopped();
  //behaviour.init_state();
  rc.Setup();
}

void loop() {
  //behaviour.update();
  rc.Update();
}

