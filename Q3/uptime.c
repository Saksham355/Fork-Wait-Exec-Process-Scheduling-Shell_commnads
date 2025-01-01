#include <stdio.h>
#include <sys/sysinfo.h>
#include <time.h> //To take the current time , the uptime and cpu info
#include <utmp.h> //To take the number of users

void display(long uptime, time_t curr, int users, double l1, double l5, double l15)
{
    int days = uptime / (24 * 3600); // Converting seconds received from uptime and converting to days hrs min sec
    uptime %= 24 * 3600;
    int hrs = uptime / 3600;
    uptime %= 3600;
    int min = uptime / 60;
    int sec = uptime % 60;

    char time_buf[9];
    struct tm *tm_info = localtime(&curr);
    strftime(time_buf, sizeof(time_buf), "%H:%M:%S", tm_info); // Current time in std format

    printf(" %s up  %02d:%02d, %d  user%s, load average: %.2f, %.2f, %.2f\n", time_buf, hrs, min, users, users == 1 ? "" : "s", l1, l5, l15);
}
// Function to get the nuber of users by incrementing the number of users every time the entry is not NULL
int get_users()
{
    struct utmp *entry;
    int users = 0;

    setutent();
    while ((entry = getutent()) != NULL)
    {
        if (entry->ut_type == USER_PROCESS)
        {
            users++;
        }
    }
    endutent();
    return users;
}

int main()
{ // Saving the cpu loads and passing all the variable in the display func.
    struct sysinfo info;
    time_t current_time;

    if (sysinfo(&info) == 0)
    {
        current_time = time(NULL);
        double l1 = info.loads[0] / 65536.0;
        double l5 = info.loads[1] / 65536.0;
        double l15 = info.loads[2] / 65536.0;
        int num_users = get_users();
        display(info.uptime, current_time, num_users, l1, l5, l15);
    }
    else
    {
        printf("Error retrieving system information.\n");
    }

    return 0;
}
