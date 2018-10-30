#ifndef COMMAND
#define COMMAND

#include <stdbool.h>

typedef struct Command {
    char *name;
    char **arguments;
    char **in_files;
    char **out_files;
    bool *mask_out_files;
    int len_in_files;
    int len_out_files;
} Command;

#endif