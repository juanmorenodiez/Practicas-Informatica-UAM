/* ===================================================================
File: command.c
Version: 2.0
Date: Feb. 18, 2018
Author: Borja Perez, Dan Roife

Description: Contains the implementation of the command interpreter

Revision history:
Feb. 10, 2018: (Seed Code)

Feb. 18, 2018: Added the commands for grabbing and dropping objects
=================================================================== */

#include <stdio.h>
#include <strings.h>
#include "command.h"

#define CMD_LENGHT 30   /*!< defines the lenght of the command */
#define N_CMD 13   /*!< defines the number of commands */

char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Grasp", "Drop", "Throw", "Check", "Move", "Turnon",  "Turnoff", "Unlock","Save", "Load"};  /*!< large name for commands */
char *short_cmd_to_str[N_CMD] =  {"","","e","g","d","t","c","m","ton","toff","u","s","l"};  /*!< short name for commands */


T_Command command_get_user_input(){

  T_Command cmd = NO_CMD;
  char input[CMD_LENGHT] = "";
  int i=UNKNOWN - NO_CMD + 1;

  if (scanf("%s", input) > 0){
    cmd = UNKNOWN;
    while(cmd == UNKNOWN && i < N_CMD){
      if (!strcasecmp(input,short_cmd_to_str[i]) || !strcasecmp(input,cmd_to_str[i])){
        cmd = i + NO_CMD;
      }
      else{
        i++;
      }
    }
  }
  return cmd;

}
