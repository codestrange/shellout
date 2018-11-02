#include <stdio.h>
#include "command.h"

void print_command(Command *command) {
    printf("Command:\n");
    printf("    Name: %s\n", command->name);
    printf("    Arguments:\n");
    for (int i = 0; i < command->len_arguments; ++i) {
        printf("        %s\n", command->arguments[i]);
    }
    printf("    Infiles:\n");
    for (int i = 0; i < command->len_in_files; ++i) {
        printf("        %s\n", command->in_files[i]);
    }
    printf("    Outfiles:\n");
    for (int i = 0; i < command->len_out_files; ++i) {
        printf("        %s: %d\n", command->out_files[i], command->mask_out_files[i]);
    }
}