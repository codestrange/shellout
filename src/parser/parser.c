#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "list.h"
#include "parser.h"

List parse(char *line) {
    Command command;
    command.name = "ls";
    command.arguments = malloc(sizeof(char*));
    command.arguments[0] = malloc(10 * sizeof(char));
    command.arguments[1] = NULL;
    command.len_in_files = 0;
    command.len_out_files = 0;
    List list = new_list(1);
    append_list(&list, command);
    return list;
}