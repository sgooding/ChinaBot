/*
 * Diagnose and test the ping sonars on my little robot.
 */

#include <NewPing.h>

#define TRIGGER_PIN_FL  49  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_FL     48  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN_C  50  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_C     51  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN_FR  53  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_FR     52  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar_fl(TRIGGER_PIN_FL, ECHO_PIN_FL, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_c(TRIGGER_PIN_C, ECHO_PIN_C, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_fr(TRIGGER_PIN_FR, ECHO_PIN_FR, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void sense(NewPing *sonar)
{
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar->ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("--------------");
  
  Serial.print(" FL: ");
  sense(&sonar_fl);

  Serial.print(" C: ");
  sense(&sonar_c);

  Serial.print(" FR: ");
  sense(&sonar_fr);
  
}
