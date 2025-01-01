#include <stdio.h>
#include <time.h>
#include <string.h>
int main(int argc, char *argv[])
{
    if (argc == 1) // std condition(IST)
    {
        time_t t;
        struct tm *ptr;
        char stdtime[100];
        time(&t);
        ptr = localtime(&t);
        strftime(stdtime, 100, "%a %d %b %Y %I:%M:%S %p IST", ptr);
        printf("%s\n", stdtime);
    }
    else
    {

        if (strcmp(argv[1], "-u") == 0) // UTC condition
        {
            struct tm *ptr;
            time_t t;
            t = time(NULL);
            ptr = gmtime(&t);
            char utctime[100];
            strftime(utctime, 100, "%a %d %b %Y %I:%M:%S %p UTC\n", ptr);
            printf("%s", utctime);
        }
        else if (strcmp(argv[1], "-r") == 0) // RFC format
        {
            time_t t;
            struct tm *ptr;
            char timeString[100];
            time(&t);
            ptr = localtime(&t);
            strftime(timeString, 100, "%a, %d %b %Y %H:%M:%S %z", ptr);
            printf("%s\n", timeString);
        }
    }
}