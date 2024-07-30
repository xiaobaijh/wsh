#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "line.h"

// This is same to the getline(),it is easier to use the getline()
char *wsh_read_line(void){
    int buffer_size = WSH_RL_BUFSIZE;
    int position = 0;
    char* buffer = (char*) malloc(sizeof(char)*buffer_size);
    int c =0;

    if (!buffer) {
        fprintf(stderr,"wsh:Fail malloc buffer\n");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        c = getchar();
        if (c==EOF || c == '\n') {
            buffer[position] = '\n';
            return buffer;
        } else{
            buffer[position++] = c;
        }
        // realloc when buffer is not enough
        if (position>buffer_size) {
            buffer_size += WSH_RL_BUFSIZE;
            buffer = (char*) realloc(buffer,buffer_size);
            if (!buffer) {
                fprintf(stderr,"wsh:Fail realloc buffer\n ");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char ** wsh_split_line(char* line) {
    int buffer_size = WSH_TOKEN_BUFSIZE,position = 0;
    char * token;
    char ** tokens = (char **)malloc(buffer_size*sizeof(char*));
    if (!tokens) {
        fprintf(stderr, "wsh:Fail malloc  token buffer\n ");
        exit(EXIT_FAILURE);
    }
    token = strtok(line,WSH_TOK_DELIM);
    while(!token){
        tokens[position++] = token;
        if (position>buffer_size) {
            buffer_size +=  WSH_TOKEN_BUFSIZE;
            tokens = (char**) realloc(tokens, buffer_size);
            if (!tokens) {
                fprintf(stderr, "wsh:Fail realloc token buffer\n ");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, WSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}