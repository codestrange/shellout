#ifndef COMMAND_LIST
#define COMMAND_LIST

#include "command.h"

typedef struct CommandList {
    Command *array;
    int size;
    int capacity;
} CommandList;

CommandList new_list(int capacity);

void insert_list(CommandList *list, int index, Command item);

void append_list(CommandList *list, Command item);

void clear_list(CommandList *list);

Command remove_list(CommandList *list, int index);

Command pop_list(CommandList *list);

Command index_list(CommandList *list, int index);

#endif