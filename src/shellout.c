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
extern int sons;
extern int *sons_pid;
char *current_dir;
char *buffer;
CharCharList history;

void signals_handler(int signal) {
    if (current_pid != -1) {
        for(int i = 0; i < sons; ++i) {
            kill(sons_pid[i], signal);
        }
        printf("\r\r");
    }
    return;
}

bool fixed_commands(char *command) {
    CommandList commands = parse(command);
    if (!commands.size)
        return true;
    Command firstcommand = index_commandlist(&commands, 0);
    if (commands.size == 1 && !strncmp(firstcommand.name, "exit", 4)  && strlen(firstcommand.name) == 4 && firstcommand.len_arguments == 1 && 
        firstcommand.len_in_files == 0 && firstcommand.len_out_files == 0) {
        set_history(&history);
        exit(0);
    } else if (commands.size == 1 && !strncmp(firstcommand.name, "cd", 2) && strlen(firstcommand.name) == 2) {
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
    }
    return false;
}

char *mygetline(void) {
    char *line = malloc(100 * sizeof(char)), *linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;
    while (true) {
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
        if ((*line++ = (char) c) == '\n')
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

int main(int argc, char **argv) {

    initialize_shell();

    while (true) {
        printf("%s$", current_dir);
        bool isOk = true;
        char *line = fixed_history_commands(&history, mygetline(), &isOk);
        if (isOk)
            save_history(&history, line);
        if (!isOk)
            printf("Problems executing the command: Event not found\n");
        else if (!fixed_commands(line)) {
            CommandList commands = parse(line);
            execute_command(commands);
        }
    }
    return 0;
}
