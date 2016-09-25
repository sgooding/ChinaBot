int sensorPin = A0;    // select the input pin for the potentiometer
unsigned long duration;
void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  duration = pulseIn(sensorPin, HIGH);
  Serial.println(duration);
  delay(100);
}
