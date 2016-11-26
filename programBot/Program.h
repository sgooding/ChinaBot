#ifndef PROGRAM_H
#define PROGRAM_H

#include <arduino.h>

#define TURN_DT_MS 200
#define MOVE_DT_MS 1000

class Program
{
  public:

  Program()
  {
    current_dt = MOVE_DT_MS;
    current_cmd_inx = 0;
    reset();
  }

  void reset()
  {  
    for(int i = 0; i < 100; i++)
    {
      command_list[i] = 0;
    }
    running = false;
    current_cmd_inx = 0; 
    is_complete = false;
  }
  
  void add_command(char command)
  {
    command_list[current_cmd_inx] = command;
    current_cmd_inx  += 1;
  }

  void update_dt(char command)
  {
    switch(command)
    {
      case 'l':
      case 'r':
        current_dt = TURN_DT_MS;
        Serial.println(TURN_DT_MS,DEC);
        break;
      default:
        current_dt = MOVE_DT_MS;
        Serial.println(MOVE_DT_MS,DEC);
    }
  }

  // execute, returns -1 if 
  // there's no new commands
  char execute()
  {
    
    char command = 0;
    if(!running)
    {
      running = true;
      start_dt = millis();
      command_list[current_cmd_inx] = '0';
      current_cmd_inx = 0;
      command = command_list[current_cmd_inx];
      update_dt(command);
      current_cmd_inx += 1;
    }
    
    if( (millis() - start_dt) > current_dt )
    {
      command = command_list[current_cmd_inx];
      update_dt(command);
      start_dt = millis();
      current_cmd_inx += 1;

      if(command_list[current_cmd_inx] == 0)
      {
        is_complete = true;
      }
      else
      {
        is_complete = false;
      }
    }
    
    return command;
  }

  bool complete()
  {
    return is_complete;
  }
  
  private:
  int current_cmd_inx;
  char command_list[100];
  long int start_dt; 
  long int current_dt;
  bool running;
  bool is_complete;
};
#endif
