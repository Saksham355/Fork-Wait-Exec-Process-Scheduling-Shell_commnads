#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

void avg() // generates the average of 4 random no.s btw 1 to 100 using math-random function.
{
    srand(time(0) ^ getpid());
    int ans = 0;
    for (int i = 0; i < 4; i++)
    {
        int n = rand() % 100;
        ans = ans + n;
    }
    ans = ans / 4;
    printf("%d\n", ans);
}

int main()
{
    srand(time(0));
    for (int i = 0; i < 7; i++) // The loop creates child processes for 7 times and executes the avg function.
    {
        int r = fork();
        if (r == 0) // checks if child process is created.
        {
            avg();
            exit(0);
        }
    }
    for (int i = 0; i < 7; i++) // The parent process waits untill the child is terminated.
    {
        wait(NULL);
    }
    return 0;
}
