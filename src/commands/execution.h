#ifndef EXECUTION
#define EXECUTION

#include "../utils/list.h"

int current_pid;
int sons;
int *sons_pid;
int execute_command(CommandList commands);

#endif
