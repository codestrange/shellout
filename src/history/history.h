#ifndef HISTORY
#define HISTORY

#include "../utils/list.h"

CharCharList get_history();

void set_history(CharCharList *history);

void print_history(CharCharList *history);

bool is_history(CharCharList *history, char *line);

void save_history(CharCharList *history, char *line);

bool try_parse_number(char **line, CharList *new, int *number);

char *fixed_history_commands(CharCharList *history, char *line);

#endif