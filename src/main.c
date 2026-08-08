#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>


#ifdef _WIN32
	#define PATH_SEP_CHAR ';'
	#define PATH_SEP_STR ';'
#else 
	#define PATH_SEP_CHAR ':'
	#define PATH_SEP_STR ':'
#endif


char *builtins[] = {"echo", "exit" , "type" };

int contains(char *arr[], int size, const char *target) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], target) == 0)
            return 1;   
    }
    return 0;           
}

int execute(const char *full_path , char *args[]){
	pid_t p = fork();
	if(p<0){
		perror("fork fail");
		return 1;
	}else if(p == 0){
		execv(full_path, args);
		perror("execv");
		return 0;
	}else{
		wait(NULL);
	}
	return 1;
}


char *find_in_path(const char *cmd, const char *path_env){
	if (path_env == NULL || *cmd == '\0' || cmd == NULL){
		return NULL;
	}
	const char *p = path_env;
    while (*p) {
      const char *end = strchr(p, PATH_SEP_CHAR);
      if (end == NULL) end = p + strlen(p);
      size_t dir_len = end - p;
      char *full_path = malloc(dir_len+strlen(cmd)+2);
      if (full_path == NULL){
      	return NULL;
      }
      
      memcpy(full_path,p,dir_len);
      full_path[dir_len] = '/';
      strcpy(full_path+dir_len+1,cmd);

	  if (access(full_path,X_OK) == 0){
	  	return full_path;
	  }
	  free(full_path);
      
      p = end;
      if (*p) p++;  
  }
  return NULL;
}


int main(int argc, char *argv[]) {


  setbuf(stdout, NULL);

   const char *path_env = getenv("PATH");
   if (path_env == NULL) {
       path_env = "/bin:/usr/bin";
   }
   char command[256];

  while(1){

	  printf("$ ");

	  fgets(command , sizeof(command), stdin);

	  char *start = command;
	  while (isspace((unsigned char)*start))
	      start++;
	  
	  size_t len = strlen(start);
	  while (len > 0 && isspace((unsigned char)start[len - 1]))
	      start[--len] = '\0';
	      
	  if(!(strcmp(start, "exit"))){
	  	break;
	  }else if (strncmp(start, "echo ", 5) == 0) {
	      printf("%s\n", start + 5);
	  }else if (strncmp(start, "type ", 5) == 0){
	  	int size = sizeof(builtins) / sizeof(builtins[0]);
	  	if (contains(builtins , size , start+5)){
	  		printf("%s is a shell builtin\n", start+5);
	  	}else{
	  		char *full_path = find_in_path(start+5 , path_env);
	  		if (full_path != NULL){
	  			printf("%s is %s\n", start+5, full_path);
	  			free(full_path);
	  		}else{
	  		printf("%s: not found\n", start+5);
	  		}
	  	}
	  }else{
	  char *cmd = strtok(start," ");
	  char *full_path = find_in_path(cmd,path_env);
	  if (full_path != NULL){
	  char *args[10];
	  int i = 0;
	  	while(cmd != NULL && i < 9){
	  		args[i++] = cmd;
	  		cmd = strtok(NULL, " ");
	  	}
	  	args[i] = NULL;
	  	
	  	execute(full_path , args);

	  	free(full_path);
	  }else{
	  printf("%s: command not found\n", start);
	  }}
	};
  return 0;
}
