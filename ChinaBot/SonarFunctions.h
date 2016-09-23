#ifndef SONAR_FUNCTIONS
#define SONAR_FUNCTIONS

#include <NewPing.h>

#define TRIGGER_PIN_FL  49  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_FL     48  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN_C  50  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_C     51  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN_FR  53  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_FR     52  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

static NewPing sonar_fl(TRIGGER_PIN_FL, ECHO_PIN_FL, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
static NewPing sonar_c(TRIGGER_PIN_C, ECHO_PIN_C, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
static NewPing sonar_fr(TRIGGER_PIN_FR, ECHO_PIN_FR, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


#endif
