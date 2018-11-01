#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/types.h>
#include <signal.h>
#include "commands/execution.h"
#include "parser/parser.h"
#include "utils/list.h"
#include "utils/command.h"
#define MAX_PATH 1000

extern int current_pid;
char *current_dir;
char *buffer;

void signals_handler(int signal) {
    if (current_pid != -1) {
        kill(current_pid, signal);
        printf("\r\r");
    }
    return;
}

bool fixed_commands (char *command) {
    if (strncmp(command, "exit", 4) == 0) {
            exit(0);
    }
    if (strncmp(command, "cd", 2) == 0) {
        CommandList commands = parse(command);
        if (commands.size == 1) {
            Command c = index_commandlist(&commands, 0);
            if (c.len_arguments == 2) {
                chdir(c.arguments[1]);
                getcwd(current_dir, MAX_PATH);
            } 
            else {
                chdir("/home");
                getcwd(current_dir, MAX_PATH);
            }
            return true;
        }
    }
    return false;
}

char * mygetline(void) {
    char * line = malloc(100 * sizeof(char)), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;
    while(true) {
        c = fgetc(stdin);
        if (c == EOF)
            break;
        if (--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);
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
}

int main(int argc, char **argv) {

    initialize_shell();

    while (true) {
        printf("%s$", current_dir);
        char *line = mygetline();
        if (!fixed_commands(line)) {
            CommandList commands = parse(line);
            execute_command(commands);
        }
    }
    return 0;
}
