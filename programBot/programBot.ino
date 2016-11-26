
#include "Program.h"
#include "MotorFunctions.h"
#include <SoftwareSerial.h>  


SoftwareSerial bluetooth(50,51);


Program program;

enum ProgramState
{
  LOAD = 0,
  PLAY,
  CLEAR,
  COMPLETE
};

ProgramState state;

void clear()
{
  program.reset();
}

void play()
{
  char next_command = program.execute();
  if (next_command == 0)
  {
    return;
  }
  Serial.print("Executing: ");
  Serial.println(next_command);
  switch(next_command)
  {
    case '0':
      stopped();
      break;
    case 'u':
      forward();
      break;
    case 'l':
      right();
      break;
    case 'r':
      left();
      break;
    case 'd':
      backward();
      break;
    default:
      break; // unhandled
  };

  if (program.complete())
  {
    state = COMPLETE;
  }
}

void load(char command)
{
  Serial.print("Loading ... ");
  Serial.println(command);
  program.add_command(command);
}

void setup() {
  // put your setup code here, to run once:
  bluetooth.begin(9600);
  Serial.begin(9600);
  setup_motors();
}

void loop() {
  // put your main code here, to run repeatedly:
  char command = 0;
  while(bluetooth.available())
  {
    command = (char)bluetooth.read();
    //Serial.println(command);
  }
  bool valid_command = false;
  switch(command)
  {
    case 'u': 
    case 'd':
    case 'l': 
    case 'r': 
      valid_command = true;
      break;
    case 's': 
      state = COMPLETE;
      break;
    case 'g': 
      state = PLAY;
      break;
  }
  
  switch(state)
  {
    case LOAD:
      if(valid_command){
      load(command);
      }
      break;
    case CLEAR:
      Serial.println("CLEAR");
      clear();
      state = LOAD;
      break;
    case PLAY:
      //Serial.println("PLAY");

      play();
      break;
    case COMPLETE:
      Serial.println("COMPLETE");
      stopped();
      state = CLEAR;
      break;
  }

  delay(100);
}
