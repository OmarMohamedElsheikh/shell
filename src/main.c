#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char command[30];
  char *exit_shell[15];
  *exit_shell = "exit";

  while(1){
	  // Flush after every printf
	  setbuf(stdout, NULL);

	  printf("$ ");

	  scanf("%s" , &command);

	  if(!(strcmp(command, *exit_shell))){
	  	break;
	  };

	  printf("%s: command not found\n", command);
	};
  return 0;
}
