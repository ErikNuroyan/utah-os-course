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
  if (argc != 3) {
    printf("Please provide 2 file names separated with a space.\n");
    exit(0);
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    printf("File to be copied couldn't be opened.\n");
    exit(1);
  }

  struct stat st;
  if (stat(argv[1], &st) == -1) {
    printf("Couldn't obtain the file info.\n");
    exit(1);
  }

  int cfd = open(argv[2], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (cfd == -1) {
    printf("The copy file couldn't be created.\n");
    exit(1);
  }

  char fileContent[st.st_size];
  if (read(fd, &fileContent, st.st_size) == -1) {
    printf("Couldn't read file content.\n");
  }
  
  if (write(cfd, fileContent, st.st_size) == -1) {
    printf("Couldn't write file content.\n");
  }

  printf("file: %s was copied to %s\n", argv[1], argv[2]);

  exit(0);
}


