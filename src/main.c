#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char command[30];


  while(1){
	  // Flush after every printf
	  setbuf(stdout, NULL);

	  printf("$ ");

	  fgets(command , sizeof(command), stdin);

	  size_t len = strlen(command);
	  if (len > 0 && command[len -1] == '\n'){
	  	command[len - 1] = '\0';
	  }

	  if(!(strcmp(command, "exit"))){
	  	break;
	  };

	  if (strncmp(command, "echo ", 5) == 0) {
	      printf("%s\n", command + 5);
	  }else{
	  printf("%s: command not found\n", command);
	  }
	};
  return 0;
}
