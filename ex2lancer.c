#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

    int pid = fork();
    if(pid == 0)
    {
        // Fils
        char *args[argc];

        for(int i = 1; i < argc; i++)
        {
            args[i-1] = argv[i];
        }
        args[argc-1] = NULL;

        execvp(argv[1], args);

        perror(argv[1]);
        exit(1);
    }
    else
    {
        // Pere
        int status;
        waitpid(pid, &status, 0);
        printf("The END");
    }

}