#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/types.h>
#include <signal.h>
#include "commands/execution.h"
#include "history/history.h"
#include "parser/parser.h"
#include "utils/list.h"
#include "utils/command.h"
#define MAX_PATH 1000

extern int current_pid;
char *current_dir;
char *buffer;
CharCharList history;

void signals_handler(int signal) {
    if (current_pid != -1) {
        kill(current_pid, signal);
        printf("\r\r");
    }
    return;
}

bool fixed_commands (char *command) {
    CommandList commands = parse(command);
    if (!commands.size)
        return true;
    Command firstcommand = index_commandlist(&commands, 0);
    if (commands.size == 1 && !strncmp(firstcommand.name, "exit", 4) && firstcommand.len_arguments == 1 && 
        firstcommand.len_in_files == 0 && firstcommand.len_out_files == 0) {
        set_history(&history);
        exit(0);
    } else if (commands.size == 1 && !strncmp(firstcommand.name, "cd", 2)) {
        if (firstcommand.len_arguments == 2) {
            if (chdir(firstcommand.arguments[1]) < 0) {
                perror("Problem opening the dir");
            }
            getcwd(current_dir, MAX_PATH);
        } else {
            chdir("/home");
            getcwd(current_dir, MAX_PATH);
        }
        return true;
    } else if (commands.size == 1 && !strncmp(firstcommand.name, "history", 7) && firstcommand.len_arguments == 1 && 
        firstcommand.len_in_files == 0 && firstcommand.len_out_files == 0) {
        CharList line;
        int cont = 0;
        for (int i = 0; i < history.size; ++i) {
            line = index_charcharlist(&history, i);
            printf("%d ", ++cont);
            for (int j = 0; j < line.size; ++j) {
                buffer = index_charlist(&line, j);
                printf("%c", buffer);
            }
            printf("%c", '\n');
        }
        return true;
    }
    return false;
}

char *mygetline(void) {
    char *line = malloc(100 * sizeof(char)), *linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;
    while(true) {
        c = fgetc(stdin);
        if (c == EOF)
            break;
        if (--len == 0) {
            len = lenmax;
            char *linen = realloc(linep, lenmax *= 2);
            if (linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }
        if ((*line++ = c) == '\n')
            break;
    }
    --line;
    *line = '\0';
    return linep;
}

void initialize_shell() {
    signal(SIGINT, signals_handler);
    current_dir = malloc(MAX_PATH * sizeof(char));
    getcwd(current_dir, MAX_PATH);
    buffer = malloc(MAX_PATH * sizeof(char));
    system("clear");
    history = get_history();
}

bool same_command(char *command) {
    CharList temp = index_charcharlist(&history, history.size - 1);
    char *lastcommand = convert_arraychar(&temp);
    while (*lastcommand && *command && *lastcommand == *command) {
        command++;
        lastcommand++;
    }
    return !*lastcommand && !*command;
}

int main(int argc, char **argv) {

    initialize_shell();

    while (true) {
        printf("%s$", current_dir);
        char *line = mygetline();
        if (!same_command(line) && *line != ' ') {
            if (history.size == 50)
                remove_charcharlist(&history, 0);
            CharList charList = new_charlist(10);
            int i = 0;
            while (line[i])
                append_charlist(&charList, line[i++]);
            append_charcharlist(&history, charList);
        }
        if (!fixed_commands(line)) {
            CommandList commands = parse(line);
            execute_command(commands);
        }
    }
    return 0;
}
