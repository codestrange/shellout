#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../utils/list.h"
#include "../utils/command.h"
#include "../history/history.h"

int current_pid = -1;
int sons = 0;
int* sons_pid = 0;
bool infirst = true;
bool outfirst = true;
extern CharCharList history;

int open_all_in(Command *command, int first_fd) {
    int def_fd = first_fd;
    for (int i = 0; i < command->len_in_files; ++i) {
        char *in_file = command->in_files[i];
        if (infirst) {
            infirst = false;
        }
        else {
            close(def_fd);
        }
        def_fd = open(in_file,O_RDONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IROTH);
    }
    return def_fd;
}

int open_all_out(Command *command, int first_fd) {
    int def_fd = first_fd;
    for (int i = 0; i < command->len_out_files; ++i) {
        char *out_file = command->out_files[i];
        bool append = command->mask_out_files[i];
        if (outfirst) {
            outfirst = false;
        }
        else {
            close(def_fd);
        }
        if (!append) {
            def_fd = open(out_file, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU | S_IRWXG | S_IROTH);
        }
        else {
            def_fd = open(out_file, O_CREAT | O_APPEND | O_WRONLY, S_IRWXU | S_IRWXG | S_IROTH);
        }
    }
    return def_fd;
}

int execute_command(CommandList commands) {
    sons = 0;
    sons_pid = malloc(commands.size * sizeof(int));
    int in = 0;
    int out = 1;
    infirst = true;
    outfirst = true;
    for (int i = 0; i < commands.size; ++i) {
        int pipes[2];
        pipe(pipes);
        out = pipes[1];
        if (i + 1 == commands.size) {
            out = 1;
            outfirst = true;
        }
        Command actual_command = index_commandlist(&commands, i);
        int command_input_fd = open_all_in(&actual_command, in);
        int command_output_fd = open_all_out(&actual_command, out);
        // //Just for debug
        // printf("comando -> %s\npipes[0] -> %d\npipes[1]-> %d\nin-> %d\nout-> %d\ncommand_in-> %d\ncommand_out-> %d\n",actual_command.name,pipes[0],pipes[1],in,out,command_input_fd,command_output_fd);
        // print_command(&actual_command);
        // //Just for debug
        int son = fork();
        sons_pid[sons++] = son;
        if (son) {
            current_pid = son;
            close(pipes[1]);
            int status;
            current_pid = -1;
            in = pipes[0];
        }
        else {
            close(pipes[0]);
            dup2(command_input_fd, 0);
            dup2(command_output_fd, 1);
            if (!strncmp(actual_command.name, "history", 7) && strlen(actual_command.name) == 7 && actual_command.len_arguments == 1 && 
                actual_command.len_in_files == 0 && actual_command.len_out_files == 0) {
                print_history(&history);
                exit(0);
            }
            else if ((!strncmp(actual_command.name, "cd", 2) && strlen(actual_command.name) == 2) || (!strncmp(actual_command.name, "exit", 4)  && strlen(actual_command.name) == 4)) {
                exit(0);
            }
            else {
                execvp(actual_command.name, actual_command.arguments);
            }
            perror("Problems executing the command");
            exit(0);
        }
    }
    while(sons--){
        int status;
        wait(&status);
    }
    free(sons_pid);
    return 0;
}