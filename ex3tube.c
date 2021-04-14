#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
  // ls | grep main

  int pid1, pid2;
  int pipefd[2];
  pipe(pipefd);
  // pipefd[0] -> lecture
  // pipefd[1] -> écriuture
  
  pid1 = fork();
  if (pid1 == 0) {
    // premier fils (ls)
    close(1);
    dup2(pipefd[1], 1);
    // le descripteur 1 correspond au côté écriture du pipe
    execlp("ls", "ls", NULL);
    exit(0);
  }

  close(pipefd[1]);
  
  pid2 = fork();
  if (pid2 == 0) {
    // 2e fils (grep main)
    dup2(pipefd[0], 0);
    // le descripteur 0 correspond au côté lecture du pipe
    execlp("grep", "grep", "ex2", NULL);
    exit(0);
  }

  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);
}