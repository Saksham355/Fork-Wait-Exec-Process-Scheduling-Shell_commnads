#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
// This code creates three child processes which execute the cal date and uptime commands by comparing the arguments passed with ./main executable generated from the makefile.
int main(int argc, char *argv[])
{
    int p1, p2, p3;
    p1 = fork();
    if (p1 == 0)
    {
        if (strcmp(argv[1], "date") == 0)
        {
            char *date[4];
            date[0] = strdup("./date");
            date[1] = argv[2];
            date[2] = argv[3];
            date[3] = NULL;
            execvp(date[0], date);
        }
        exit(0);
    }
    p2 = fork();
    if (p2 == 0)
    {
        if (strcmp(argv[1], "cal") == 0)
        {
            char *date[4];
            date[0] = strdup("./cal");
            date[1] = argv[2];
            date[2] = argv[3];
            date[3] = NULL;
            execvp(date[0], date);
        }
        exit(0);
    }
    p3 = fork();
    if (p3 == 0)
    {
        if (strcmp(argv[1], "uptime") == 0)
        {
            char *date[2];
            date[0] = strdup("./uptime");
            date[1] = NULL;
            execvp(date[0], date);
        }
        exit(0);
    }
    // Parent process waits for all the three child processes to terminate.
    wait(0);
    wait(0);
    wait(0);
    return 0;
}