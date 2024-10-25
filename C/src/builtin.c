#include "builtin.h"

#include <stdio.h>
#include <unistd.h>

char *builtin_str[] = {"cd", "help", "exit"};
int (*builtin_func[])(char **) = {&wsh_cd, &wsh_help, &wsh_exit};
int wsh_builtins_nums() {
  return sizeof(builtin_func) / sizeof(builtin_func[0]);
}

int wsh_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "expected argument to cd \n");
  } else if (chdir(args[1]) != 0) {
    perror("wsh cd error");
  }
  return 1;
}

int wsh_help(char **args) {
  int i;
  printf("Wang's Shell\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");
  int num = wsh_builtins_nums();
  for (i = 0; i < num; i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("glad to use it.\n");
  return 1;
}

int wsh_exit(char **args) { return 0; }
