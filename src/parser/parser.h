#ifndef PARSER
#define PARSER

#include "../utils/list.h"

CharCharList split(char *str);

Command parse_command(CharCharList *charCharList, int *index);

CommandList parse(char *line);

#endif