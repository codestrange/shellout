#include <stdio.h>
#include <stdlib.h>
#include "../utils/command.h"
#include "../utils/list.h"
#include "parser.h"

List parse(char *line) {
    Command command;
    command.name = "ls";
    command.arguments = malloc(3 * sizeof(char*));
    command.arguments[0] = malloc(10 * sizeof(char));
    command.arguments[0] = "ls";
    command.arguments[1] = NULL;
    command.out_files = malloc(sizeof(char*));
    command.out_files[0] = malloc(10 * sizeof(char));
    command.out_files[0] = "files/a.txt";
    command.mask_in_files = malloc(sizeof(bool*));
    command.mask_in_files[0] = false;
    command.len_in_files = 0;
    command.len_out_files = 1;

    Command command1;
    command1.name = "grep";
    command1.arguments = malloc(3 * sizeof(char*));
    command1.arguments[0] = malloc(10 * sizeof(char));
    command1.arguments[0] = "grep";
    command1.arguments[1] = malloc(10 * sizeof(char));
    command1.arguments[1] = "i";
    command1.arguments[2] = NULL;
    command1.in_files = malloc(sizeof(char*));
    command1.in_files[0] = malloc(10 * sizeof(char));
    command1.in_files[0] = "files/a.txt";
    command1.mask_in_files = malloc(sizeof(bool*));
    command1.mask_in_files[0] = false;
    command1.len_in_files = 1;
    command1.len_out_files = 0;

    Command command2;
    command2.name = "grep";
    command2.arguments = malloc(3 * sizeof(char*));
    command2.arguments[0] = malloc(10 * sizeof(char));
    command2.arguments[0] = "grep";
    command2.arguments[1] = malloc(10 * sizeof(char));
    command2.arguments[1] = "e";
    command2.arguments[2] = NULL;
    command2.len_in_files = 0;
    command2.len_out_files = 0;

    List list = new_list(10);
    append_list(&list, command);
    append_list(&list, command1);
    append_list(&list, command2);
    return list;
}