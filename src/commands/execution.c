#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int execute_command(char *command, char **args) {
    int son = fork();
    if(son) {
        int status;
        waitpid(son, &status, 0);
    }
    else {
        execvp(command, args);
        return -1;
    }
    return 0;
}