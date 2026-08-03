#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  char *command[30];
  // Flush after every printf
  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
  printf("$ ");

  scanf("%s" , &command);

  printf("%s: command not found", command);

  return 0;
}
