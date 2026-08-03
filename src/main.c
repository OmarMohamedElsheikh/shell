#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *builtins[] = {"echo", "exit" , "type"};

int contains(char *arr[], int size, const char *target) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], target) == 0)
            return 1;   
    }
    return 0;           
}


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

	  char *start = command;
	  while (isspace((unsigned char)*start))
	      start++;
	  
	  size_t lenc = strlen(start);
	  while (len > 0 && isspace((unsigned char)start[lenc - 1]))
	      start[--lenc] = '\0';
	      
	  if(!(strcmp(start, "exit"))){
	  	break;
	  }else if (strncmp(start, "echo ", 5) == 0) {
	      printf("%s\n", start + 5);
	  }else if (strncmp(start, "type ", 5) == 0){
	  	int size = sizeof(builtins) / sizeof(builtins[0]);
	  	if (contains(builtins , size , start+5)){
	  		printf("%s is a shell builtin\n", start+5);
	  	}else{
	  		printf("%s: not found\n", start+5);
	  	}
	  }else{
	  printf("%s: command not found\n", start);
	  }
	};
  return 0;
}
