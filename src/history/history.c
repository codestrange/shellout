#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../utils/list.h"
#include "../parser/parser.h"

CharCharList get_history() {
    int fd = open("/tmp/.shellout_history", O_CREAT | O_RDONLY, 0664);
    CharCharList history = new_charcharlist(10);
    CharList line = new_charlist(10);
    char buffer;
    while (read(fd, &buffer, 1)) {
        if (buffer == 10) {
            if (line.size) {
                append_charcharlist(&history, line);
                line = new_charlist(10);
            }
        } else
            append_charlist(&line, buffer);
    }
    if (line.size) {
        append_charcharlist(&history, line);
    }
    close(fd);
    return history;
}

void set_history(CharCharList *history) {
    int fd = open("/tmp/.shellout_history", O_CREAT | O_WRONLY | O_TRUNC, 0664);
    char buffer;
    CharList line;
    for (int i = 0; i < history->size; ++i) {
        line = index_charcharlist(history, i);
        for (int j = 0; j < line.size; ++j) {
            buffer = index_charlist(&line, j);
            write(fd, &buffer, 1);
        }
        if (i + 1 != history->size) {
            buffer = '\n';
            write(fd, &buffer, 1);
        }
    }
    close(fd);
}

void print_history(CharCharList *history) {
    CharList line;
    char buffer;
    int cont = 0;
    for (int i = 0; i < history->size; ++i) {
        line = index_charcharlist(history, i);
        printf("%d ", ++cont);
        for (int j = 0; j < line.size; ++j) {
            buffer = index_charlist(&line, j);
            printf("%c", buffer);
        }
        printf("%c", '\n');
    }
}

bool is_history(CharCharList *history, char *line) {
    if (*line == ' ')
        return false;
    CharList temp = index_charcharlist(history, history->size - 1);
    char *lastcommand = convert_arraychar(&temp);
    while (*lastcommand && *line && *lastcommand == *line) {
        line++;
        lastcommand++;
    }
    return *lastcommand || *line;
}

void save_history(CharCharList *history, char *line) {
    if (is_history(history, line)) {
        if (history->size == 50)
            remove_charcharlist(history, 0);
        CharList charList = new_charlist(10);
        int i = 0;
        while (line[i])
            append_charlist(&charList, line[i++]);
        append_charcharlist(history, charList);
    }
}

bool try_parse_number(char **line, CharList *new, int *number) {
    *number = 0;
    bool is_number = true;
    while (**line) {
        if (**line == ' ' || **line == '|' || **line == '>' || **line == '<') {
            break;
        }
        append_charlist(new, **line);
        if (**line < 48 || **line > 57) {
            is_number = false;
        }
        *number = *number * 10 + **line - 48;
        (*line)++;
    }
    return is_number;
}

char *fixed_history_commands(CharCharList *history, char *line) {
    CharList result = new_charlist(50);
    while (*line) {
        if (*line != '!') {
            append_charlist(&result, *line);
            line++;
        } else {
            line++;
            if (!*line) {
                append_charlist(&result, '!');
                break;
            }
            int number = 0;
            CharList command = new_charlist(10);
            if (try_parse_number(&line, &command, &number)) {
                if (number <= history->size && number > 0) {
                    CharList charList = index_charcharlist(history, number - 1);
                    for (int j = 0; j < charList.size; ++j) {
                        append_charlist(&result, index_charlist(&charList, j));
                    }
                } else {
                    append_charlist(&result, '!');
                    for (int j = 0; j < command.size; ++j) {
                        append_charlist(&result, index_charlist(&command, j));
                    }
                }
            } else if (command.size == 1 && index_charlist(&command, 0) == '!') {
                if (history->size > 0) {
                    CharList charList = index_charcharlist(history, history->size - 1);
                    for (int j = 0; j < charList.size; ++j) {
                        append_charlist(&result, index_charlist(&charList, j));
                    }
                } else {
                    append_charlist(&result, '!');
                    append_charlist(&result, '!');
                }
            } else {
                char *firstcommand = convert_arraychar(&command);
                int len = (int) strlen(firstcommand);
                bool is_correct = false;
                for (int j = history->size - 1; j >= 0; --j) {
                    CharList charList = index_charcharlist(history, j);
                    char *temp = convert_arraychar(&charList);
                    CommandList tempcommands = parse(temp);
                    Command tempfirstcommand = index_commandlist(&tempcommands, 0);
                    if (!strncmp(tempfirstcommand.name, firstcommand, len)) {
                        for (int k = 0; k < charList.size; ++k) {
                            append_charlist(&result, index_charlist(&charList, k));
                        }
                        is_correct = true;
                        break;
                    }
                }
                if (!is_correct) {
                    append_charlist(&result, '!');
                    for (int j = 0; j < command.size; ++j) {
                        append_charlist(&result, index_charlist(&command, j));
                    }
                }
            }
        }
    }
    return convert_arraychar(&result);
}