#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../utils/list.h"
#include "../utils/command.h"

bool infirst = true;
bool outfirst = true;

int open_all_in(Command *command, int first_fd) {
    int def_fd = first_fd;
    for(int i = 0; i < command->len_in_files; ++i) {
        char *in_file = command->in_files[i];
        if(infirst) {
            infirst = false;
        }
        else {
            close(def_fd);
        }
        def_fd = open(in_file,O_RDONLY | O_CREAT);
    }
    return def_fd;
}

int open_all_out(Command *command,int first_fd) {
    int def_fd = first_fd;
    for(int i = 0; i < command->len_out_files; ++i) {
        char *out_file = command->out_files[i];
        bool append = command->mask_in_files[i];
        if(outfirst) {
            outfirst = false;
        }
        else {
            close(def_fd);
        }
        if(append)
            def_fd = open(out_file, O_CREAT | O_TRUNC | O_WRONLY);
        else
            def_fd = open(out_file, O_CREAT | O_APPEND | O_WRONLY);
    }
    return def_fd;
}

int execute_command(List commands) {
    int in = 0;
    int out = 1;
    for(int i = 0; i < commands.size; ++i) {
        int pipes[2];
        pipe(pipes);
        out = pipes[1];
        Command actual_command = index_list(&commands, i);
        int command_input_fd = open_all_in(&actual_command, in);
        int command_output_fd = open_all_out(&actual_command, out);

        int son = fork();
        if(son) {
            close(pipes[2]);
            int status;
            wait(&status);
            in = pipes[1];
            char c;
            if(i + 1 == commands.size) {
                while(read(in,&c,1)) {
                    write(stdout,&c,1);
                    if(c == EOF)
                }
            }
            else if(command_output_fd != in) {
                while(read(in,&c,1)) {
                    write(command_output_fd,&c,1);
                }
            }
        }
        else {
            close(pipes[1]);
            dup2(command_input_fd, 0);
            dup2(pipes[2], 1);
            execvp(actual_command.name, actual_command.arguments);
        }
    }

    return 0;
}