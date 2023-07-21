#include "commands.h"
#include "my_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void execmd(char **argv){
    char *command = NULL, *actual_command = NULL;

    if (argv){
        /* get the command */
        command = argv[0];

        /* generate the path to this command before passing it to execve */
        actual_command = get_location(command);

        /* execute the actual command with execve */
        if (execve(actual_command, argv, NULL) == -1){
            perror("Error:");
        }
    }

}
