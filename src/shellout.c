#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include "commands/execution.h"
#include "parser/parser.h"
#include "utils/list.h"
#include "utils/command.h"
#define MAX_PATH 1000

int current_pid;
char *current_dir;
char *buffer;

char * mygetline(void) {
    char * line = malloc(100 * sizeof(char)), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;
    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;
        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);
            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }
        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

void initialize_shell() {
    current_dir = malloc(MAX_PATH * sizeof(char));
    getcwd(current_dir, MAX_PATH);
    buffer = malloc(MAX_PATH * sizeof(char));
    system("clear");
}

int main(int argc, char **argv) {

    initialize_shell();

    while(true) {
        printf("%s$", current_dir);
        char *line = mygetline();
        CommandList commands = parse(line);
        execute_command(commands);
    }
    return 0;
}
