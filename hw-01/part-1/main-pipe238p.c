#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  if (argc > 1) {
    printf("Please don't provide additional arguments.\n");
    exit(1);
  }

  int pipe1[2];
  pipe(pipe1);

  int pid = fork();
  if (pid == 0) {
    // Write to the write end of the pipe
    dup2(pipe1[1], STDOUT_FILENO);
    close(pipe1[1]);
    close(pipe1[0]);
    execlp("ls", "ls", NULL);
  }

  int pipe2[2];
  pipe(pipe2);

  pid = fork();
  if (pid == 0) {
    dup2(pipe1[0], STDIN_FILENO);
    close(pipe1[0]);
    close(pipe1[1]);

    dup2(pipe2[1], STDOUT_FILENO);
    close(pipe2[0]);
    close(pipe2[1]);
    execlp("grep", "grep", "main-pipe238p", NULL);
  }
  
  dup2(pipe2[0], STDIN_FILENO);
  close(pipe1[0]);
  close(pipe1[1]);
  close(pipe2[0]);
  close(pipe2[1]);

  execlp("wc", "wc", NULL);

  exit(0);
}


