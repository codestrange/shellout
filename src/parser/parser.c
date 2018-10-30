#include <stdio.h>
#include <stdlib.h>
#include "../utils/command.h"
#include "../utils/list.h"
#include "parser.h"

List parse(char *line) {
    Command command;
    command.name = "ls";
    command.arguments = malloc(sizeof(char*));
    command.arguments[0] = malloc(10 * sizeof(char));
    command.arguments[0][0] = '-';
    command.arguments[0][0] = 'l';
    command.arguments[0][0] = 0;
    command.arguments[1] = NULL;
    command.len_in_files = 0;
    command.len_out_files = 0;
    List list = new_list(1);
    append_list(&list, command);
    return list;
}