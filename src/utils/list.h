#ifndef LIST
#define LIST

#include "command.h"

typedef struct List {
    Command *array;
    int size;
    int capacity;
} List;

List new_list(int capacity);

void insert_list(List *list, int index, Command item);

void append_list(List *list, Command item);

void clear_list(List *list);

Command remove_list(List *list, int index);

Command pop_list(List *list);

Command index_list(List *list, int index);

#endif