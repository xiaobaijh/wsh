#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtin.h"
#include "line.h"

void wsh_loop();
int wsh_execute(char **args);
int wsh_launch(char **args);

int main() {
  wsh_loop();
  return EXIT_SUCCESS;
}

void wsh_loop() {
  char *line;
  char **args;
  int status = 1;

  do {
    printf("wsh> ");
    line = wsh_read_line();
    args = wsh_split_line(line);
    status = wsh_execute(args);
    free(line);
    free(args);
  } while (status);
}

int wsh_execute(char **args) {
  extern char *builtin_str[];
  extern int (*builtin_func[])(char **);
  int i;
  if (args[0] == NULL) {
    return 1;
  }
  for (i = 0; i < wsh_builtins_nums(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  return wsh_launch(args);
}

int wsh_launch(char **args) {
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Pid==0 means run child process now,so we can exec what we want
    // The execvp() recevied args as a vector,it will search the args[0] in the
    // PATH and run it
    if (execvp(args[0], args) == -1) {
      perror("wsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Pid<0 (-1) means fail to create a child process
    perror("wsh");
  } else {
    // pid>0 means run father process now and the child process is going to
    // exec,so we ues  waitpid() to wait for the process’s state to change
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}
