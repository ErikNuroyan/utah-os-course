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
  if (argc != 1) {
    printf("Please don't provide additional arguments.\n");
    exit(1);
  }
  
  close(1); // Closes the standard output
  int fd = open("y.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd != 1) {
    printf("Error opening the file y.\n");
    exit(1);
  }

  if (execlp("ls", "ls") == -1) {
    printf("Error executing ls.\n");
    exit(1);
  }

  exit(0);
}


