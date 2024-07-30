#include <stdio.h>

#include "line.h"
using namespace std;

void wsh_loop();
int wsh_execute(char** args);

int main()
{
    wsh_loop();
    return EXIT_SUCCESS;
}


void wsh_loop()
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("wsh> ");
        line = wsh_read_line();  
        args = wsh_split_line(line);
        status = wsh_execute(args);

        free(line);
        free(args);
    } while (status);
}

int wsh_execute(char** args) {
    // TODO
    return 0;
}

