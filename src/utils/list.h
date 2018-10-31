#ifndef LIST
#define LIST

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
// #include <wchar.h>
#include "command.h"

#define ARGUMENT 0
#define INFILE 1
#define OUTFILE_REPLACE 2
#define OUTFILE_APPEND 3

typedef struct CommandList {
    Command *array;
    int size;
    int capacity;
} CommandList;

typedef struct CharList {
    char *array;
    int size;
    int capacity;
} CharList;

typedef struct CharCharList {
    CharList *array;
    int size;
    int capacity;
} CharCharList;

typedef struct BoolList {
    bool *array;
    int size;
    int capacity;
} BoolList;

CommandList new_commandlist(int capacity);

void insert_commandlist(CommandList *list, int index, Command item);

void append_commandlist(CommandList *list, Command item);

void clear_commandlist(CommandList *list);

Command remove_commandlist(CommandList *list, int index);

Command pop_commandlist(CommandList *list);

Command index_commandlist(CommandList *list, int index);

CharList new_charlist(int capacity);

void insert_charlist(CharList *list, int index, char item);

void append_charlist(CharList *list, char item);

void clear_charlist(CharList *list);

char remove_charlist(CharList *list, int index);

char pop_charlist(CharList *list);

char index_charlist(CharList *list, int index);

CharCharList new_charcharlist(int capacity);

void insert_charcharlist(CharCharList *list, int index, CharList item);

void append_charcharlist(CharCharList *list, CharList item);

void clear_charcharlist(CharCharList *list);

CharList remove_charcharlist(CharCharList *list, int index);

CharList pop_charcharlist(CharCharList *list);

CharList index_charcharlist(CharCharList *list, int index);

BoolList new_boollist(int capacity);

void insert_boollist(BoolList *list, int index, bool item);

void append_boollist(BoolList *list, bool item);

void clear_boollist(BoolList *list);

bool remove_boollist(BoolList *list, int index);

bool pop_boollist(BoolList *list);

bool index_boollist(BoolList *list, int index);

char *convert_arraychar(CharList *charList);

char **convert_arraycharchar(CharCharList *charCharList);

bool *convert_boolchar(BoolList *boolList);

#endif