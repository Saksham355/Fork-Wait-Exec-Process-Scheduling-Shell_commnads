#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    char *month = argv[1]; // Taking month,year args.
    char *year = argv[2];
    int m_no;
    int n_days;

    if (strcmp(month, "January") == 0) // Setting month no and respective no. of days.
    {
        m_no = 1;
        n_days = 31;
    }
    else if (strcmp(month, "February") == 0)
    {
        m_no = 2;
        n_days = 28;
    }
    else if (strcmp(month, "March") == 0)
    {
        m_no = 3;
        n_days = 31;
    }
    else if (strcmp(month, "April") == 0)
    {
        m_no = 4;
        n_days = 30;
    }
    else if (strcmp(month, "May") == 0)
    {
        m_no = 5;
        n_days = 31;
    }
    else if (strcmp(month, "June") == 0)
    {
        m_no = 6;
        n_days = 30;
    }
    else if (strcmp(month, "July") == 0)
    {
        m_no = 7;
        n_days = 31;
    }
    else if (strcmp(month, "August") == 0)
    {
        m_no = 8;
        n_days = 31;
    }
    else if (strcmp(month, "September") == 0)
    {
        m_no = 9;
        n_days = 30;
    }
    else if (strcmp(month, "October") == 0)
    {
        m_no = 10;
        n_days = 31;
    }
    else if (strcmp(month, "November") == 0)
    {
        m_no = 11;
        n_days = 30;
    }
    else if (strcmp(month, "December") == 0)
    {
        m_no = 12;
        n_days = 31;
    }
    else
    {
        printf("Error: Invalid_month\n");
        return 0;
    }
    char cal_header[100];
    strcpy(cal_header, "    "); // Creating a heading for the month,year,days of the week.
    strcat(cal_header, month);
    strcat(cal_header, " ");
    strcat(cal_header, year);
    printf("%s\n", cal_header);
    printf("Su Mo Tu We Th Fr Sa\n");
    int y = atoi(year); // leap year condition
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
    {
        if (m_no == 2)
        {
            n_days = 29;
        }
    }

    int d = 1;
    int m = m_no; // Changing the month no. and year for JAN and FEB,to accomodate them according to the Zellers formula
    if (m == 1 || m == 2)
    {
        m += 12;
        y -= 1;
    }
    int k = y % 100;
    int j = y / 100;
    int h = (d + (13 * (m + 1) / 5) + k + (k / 4) + (j / 4) - 2 * j + 5) % 7; // Zellers formula

    int day = h + 1;
    // printing format for the dates of the month
    if (day <= 6)
    {
        for (int i = 0; i < day * 3; i++)
        {
            printf(" ");
        }
    }

    for (int i = 1; i <= n_days; i++)
    {
        printf("%2d ", i);
        if ((i + day) % 7 == 0)
        {
            printf("\n");
        }
    }

    if ((n_days + day) % 7 != 0)
    {
        printf("\n");
    }

    return 0;
}
