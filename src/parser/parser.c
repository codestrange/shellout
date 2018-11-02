#include <stdio.h>
#include <stdlib.h>
#include "../utils/command.h"
#include "../utils/list.h"
#include "parser.h"

CharCharList split(char *str) {
    CharCharList charCharList = new_charcharlist(10);
    CharList charList = new_charlist(10);
    while (true) {
        if (*str == ' ' || *str == 0) {
            if (charList.size) {
                append_charcharlist(&charCharList, charList);
                charList = new_charlist(10);
            }
            if (*str == 0)
                break;
        } else if (*str == '<' || *str == '>' || *str == '|') {
            if (charList.size) {
                append_charcharlist(&charCharList, charList);
                charList = new_charlist(10);
            }
            append_charlist(&charList, *str);
            if (*str == '>' && *(str + 1) == '>') {
                append_charlist(&charList, *str);
                str++;
            }
            append_charcharlist(&charCharList, charList);
            charList = new_charlist(10);
        } else
            append_charlist(&charList, *str);
        str++;
    }
    return charCharList;
}

Command parse_command(CharCharList *charCharList, int *index) {
    Command command;
    CharList name = new_charlist(10);
    CharCharList arguments = new_charcharlist(10);
    CharCharList in_files = new_charcharlist(10);
    CharCharList out_files = new_charcharlist(10);
    BoolList mask_out_files = new_boollist(10);
    name = index_charcharlist(charCharList, *index);
    append_charcharlist(&arguments, name);
    (*index)++;
    while (charCharList->size != *index) {
        CharList charList = index_charcharlist(charCharList, *index);
        int option;
        if (charList.size == 1 && index_charlist(&charList, 0) == '<') {
            option = INFILE;
            (*index)++;
        } else if (charList.size == 1 && index_charlist(&charList, 0) == '>') {
            option = OUTFILE_REPLACE;
            (*index)++;
        } else if (charList.size == 2 && index_charlist(&charList, 0) == '>' && index_charlist(&charList, 1) == '>') {
            option = OUTFILE_APPEND;
            (*index)++;
        } else {
            option = ARGUMENT;
        }
        if(charCharList->size == *index)
            break;
        if(charList.size == 1 && index_charlist(&charList, 0) == '|')
            break;
        charList = index_charcharlist(charCharList, *index);
        switch (option) {
            case ARGUMENT:
                append_charcharlist(&arguments, charList);
                break;
            case INFILE:
                append_charcharlist(&in_files, charList);
                break;
            default:
                append_charcharlist(&out_files, charList);
                append_boollist(&mask_out_files, option == OUTFILE_APPEND);
                break;
        }
        (*index)++;
    }
    command.name = convert_arraychar(&name);
    command.arguments = convert_arraycharchar(&arguments);
    command.in_files = convert_arraycharchar(&in_files);
    command.out_files = convert_arraycharchar(&out_files);
    command.mask_out_files = convert_boolchar(&mask_out_files);
    command.len_in_files = in_files.size;
    command.len_out_files = out_files.size;
    command.len_arguments = arguments.size;
    return command;
}

CommandList parse(char *str) {
    CharCharList charCharList = split(str);
    CommandList commandList = new_commandlist(10);
    Command command;
    for (int i = 0; i < charCharList.size; ++i) {
        command = parse_command(&charCharList, &i);
        append_commandlist(&commandList, command);
    }
    return commandList;
}