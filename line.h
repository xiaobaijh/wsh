#ifndef LINE_H
#define LINE_H
#endif

#include <stdlib.h>
#define WSH_RL_BUFSIZE 1024
#define WSH_TOKEN_BUFSIZE 64
#define WSH_TOK_DELIM " \t\r\n\a"

char *wsh_read_line(void);
char **wsh_split_line(char *line);