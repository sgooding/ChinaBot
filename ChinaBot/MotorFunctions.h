#ifndef MOTOR_FUNCTIONS
#define MOTOR_FUNCTIONS

static int pwm_a = 3;   //PWM control for motor outputs 1 and 2 is on digital pin 3
static int pwm_b = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
static int dir_a = 12;  //direction control for motor outputs 1 and 2 is on digital pin 12
static int dir_b = 13; //direction control for motor outputs 3 and 4 is on digital pin 13
#define SPEED 200

static void setup_motors()
{
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);
}

static void forward() //full speed forward
{ 
  digitalWrite(dir_a, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite(dir_b, LOW);  //Reverse motor direction, 3 low, 4 high  
  analogWrite(pwm_a, SPEED);    //set both motors to run at (100/255 = 39)% duty cycle
  analogWrite(pwm_b, SPEED);
}

static void backward() //full speed backward
{
  digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
  digitalWrite(dir_b, HIGH);  //Set motor direction, 3 high, 4 low
  analogWrite(pwm_a, SPEED);   //set both motors to run at 100% duty cycle (fast)
  analogWrite(pwm_b, SPEED);
}

static void right() //full speed right
{
  digitalWrite(dir_a, HIGH);  //Set motor direction, 1 low, 2 high
  digitalWrite(dir_b, HIGH);  //Set motor direction, 3 high, 4 low
  analogWrite(pwm_a, SPEED);   //set both motors to run at 100% duty cycle (fast)
  analogWrite(pwm_b, SPEED);
}

static void left() //full speed right
{
  digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
  digitalWrite(dir_b, LOW);  //Set motor direction, 3 high, 4 low
  analogWrite(pwm_a, SPEED);   //set both motors to run at 100% duty cycle (fast)
  analogWrite(pwm_b, SPEED);
}



static void stopped() //stop
{ 
  digitalWrite(dir_a, LOW); //Set motor direction, 1 low, 2 high
  digitalWrite(dir_b, LOW); //Set motor direction, 3 high, 4 low
  analogWrite(pwm_a, 0);    //set both motors to run at 100% duty cycle (fast)
  analogWrite(pwm_b, 0); 
}

#endif
