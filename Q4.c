#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define bool int
#define true 1
#define false 0
struct process // creating a process structure with all required attributes.
{
    int pid;
    int arr_time;
    int burst;
    int quantum;
    int comp;
    int resp;
    bool visited;
};
void sort_arrival(int n, struct process *arr) // Will sort the process array on the bases of arrival time using bubble sort.
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].arr_time > arr[j + 1].arr_time)
            {
                struct process temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void sort_burst(int n, struct process *arr) // Will sort the process array on the bases of cpu burst time using bubble sort.
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].burst > arr[j + 1].burst)
            {
                struct process temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void setprocess(int n, struct process *arr1, struct process *arr2) // Save all the info about the processes in two process arrays.
{
    for (int i = 0; i < n; i++)
    {
        printf("Process ID:");
        scanf("%d", &arr1[i].pid);
        arr2[i].pid = arr1[i].pid;
        printf("Arrival Time:");
        scanf("%d", &arr1[i].arr_time);
        arr2[i].arr_time = arr1[i].arr_time;
        printf("Burst Time:");
        scanf("%d", &arr1[i].burst);
        arr2[i].burst = arr1[i].burst;
        printf("\n");
    }
    printf("Time quantum for round robin:");
    int r;
    scanf("%d", &r);
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        arr1[i].quantum = r;
        arr2[i].quantum = r;
    }
}
void fifo(int n, struct process *arr) // Executes the first in first out scheduling policy.
{
    int ct = 0;           // A timer to count the duration
    sort_arrival(n, arr); // Sorts the array on arrival basis
    printf("Order of execution: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i].pid);
        if (arr[i].arr_time > ct) // checks if the process has arrived or not
        {
            arr[i].resp = 0;
            arr[i].comp = ct + arr[i].burst - arr[i].arr_time; // code for not arrived
            ct = arr[i].arr_time + arr[i].burst;
        }
        else
        {
            arr[i].resp = ct - arr[i].arr_time;
            arr[i].comp = ct + arr[i].burst - arr[i].arr_time; // code if already arrived
            ct += arr[i].burst;
        }
    }
    // calculates and prints the avg resp and avg tat
    printf("\n");
    float sum1 = 0;
    for (int i = 0; i < n; i++)
    {
        sum1 += arr[i].resp;
    }
    sum1 /= n;
    printf("Average response time:%.2f\n", sum1);
    float sum2 = 0;
    for (int i = 0; i < n; i++)
    {
        sum2 += arr[i].comp;
    }
    sum2 /= n;
    printf("Average turn-around time:%.2f\n", sum2);
}
void sjf(int n, struct process *arr) // Executes the shortest job first scheduling policy
{
    sort_arrival(n, arr); // sort on arrival bases

    int ct = 0;
    int completed = 0; // to keep a check if all the process are executed or not.
    float sum_resp = 0, sum_tat = 0;

    for (int i = 0; i < n; i++)
    {
        arr[i].visited = false; // For the purpose of not repeteadly run the same process while iterating through the process array again and again
    }

    printf("Order of execution: ");

    while (completed < n)
    {
        int next_p = -1;
        int min_burst = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (arr[i].arr_time <= ct && arr[i].visited == false && arr[i].burst < min_burst) // finds the process with minimum burst time,and set it as visited
            {
                next_p = i;
                min_burst = arr[i].burst;
            }
        }

        if (next_p != -1) // Enters the response time and turnaround time for the process
        {
            arr[next_p].resp = ct - arr[next_p].arr_time;
            ct += arr[next_p].burst;
            arr[next_p].comp = ct;
            arr[next_p].visited = true;

            printf("%d ", arr[next_p].pid); // prints the process id for the order of execution

            sum_resp += arr[next_p].resp;
            sum_tat += arr[next_p].comp - arr[next_p].arr_time;

            completed++;
        }
        else
        {
            ct++;
        }
    }

    printf("\n");
    printf("Average response time: %.2f\n", sum_resp / n);
    printf("Average turnaround time: %.2f\n", sum_tat / n);
}
void robin(int n, struct process *arr) // Executes the round robin scheduling policy.
{
    sort_arrival(n, arr); // sorts the processes on the basis of arrival
    printf("\n");
    int ct = 0;
    int q = arr[0].quantum; // takes the quantum time.
    bool allcompleted = false;
    int total_resp = 0, total_tat = 0;
    int completed = 0;

    for (int i = 0; i < n; i++) // Sets all processes as not visited
    {
        arr[i].visited = false;
    }

    printf("Order of execution: ");

    while (!allcompleted)
    {
        allcompleted = true;

        for (int i = 0; i < n; i++)
        {
            if (arr[i].arr_time <= ct && arr[i].burst > 0) // if the process has arrived
            {
                allcompleted = false;

                if (!arr[i].visited) // if its not visited
                {
                    arr[i].resp = ct - arr[i].arr_time; // set the response time
                    arr[i].visited = true;              // set it at visited
                    total_resp += arr[i].resp;
                }
                printf("%d ", arr[i].pid); // printing the order

                if (arr[i].burst >= q) // if the remaining execution time of the process is greater than the time quantum
                {
                    arr[i].burst -= q; // decrease the time quantum from burst time and update the timer
                    ct += q;
                }
                else
                {
                    ct += arr[i].burst; // else set the burst time as 0 and update the timer
                    arr[i].burst = 0;
                }

                if (arr[i].burst == 0) // if a process is completed then caculate then set the tat
                {
                    arr[i].comp = ct - arr[i].arr_time;
                    total_tat += arr[i].comp;
                    completed++;
                }
            }
        }
    }
    printf("\nAverage Response Time: %.2f\n", (float)total_resp / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

void srtf(int n, struct process *arr)
{
    int rtime[n];
    for (int i = 0; i < n; i++) // Stores the runtime of all processes in a seperate array.
    {
        rtime[i] = arr[i].burst;
    }

    int ct = 0;
    int completed = 0;
    float sum_resp = 0, sum_tat = 0;
    bool firstex[n]; // to keep a check if process is first executed or not
    bool queue[n];   // if the process is still in queue(to be executed again).

    for (int i = 0; i < n; i++) // Setting to default state
    {
        firstex[i] = false;
        queue[i] = false;
    }

    printf("Order of execution: ");

    while (completed < n)
    {
        int next_p = -1;
        int min_burst = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (arr[i].arr_time <= ct && rtime[i] > 0 && rtime[i] < min_burst) // Similar to SJF
            {
                next_p = i;
                min_burst = rtime[i];
            }
        }

        if (next_p != -1)
        {
            if (!firstex[next_p]) // if executed first time then set the response time.
            {
                arr[next_p].resp = ct - arr[next_p].arr_time;
                sum_resp += arr[next_p].resp;
                firstex[next_p] = true;
            }

            printf("%d ", arr[next_p].pid); // Printing pid for execution order.
            rtime[next_p]--;                // Reducing the burst time of the last executed process to one sec and -->
            ct++;                           //-->going again to get the process of minimum burst time including the visited processes.

            if (rtime[next_p] == 0) // if process completed then set the tat.
            {
                completed++;
                arr[next_p].comp = ct;
                sum_tat += arr[next_p].comp - arr[next_p].arr_time;
            }
        }
        else
        {
            ct++;
        }
    }

    printf("\n");
    printf("Average response time: %.2f\n", sum_resp / n);
    printf("Average turnaround time: %.2f\n", sum_tat / n);
}

int main() // Initiating two process arrays,saving all process info and calling the four policies on them
{
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);
    struct process *arr1 = (struct process *)malloc(n * sizeof(struct process));
    struct process *arr2 = (struct process *)malloc(n * sizeof(struct process));
    setprocess(n, arr1, arr2);
    printf("FIFO:\n");
    fifo(n, arr1);
    printf("SJF:\n");
    sjf(n, arr1);
    printf("SRTF:\n");
    srtf(n, arr1);
    printf("ROBIN:");
    robin(n, arr2);
    free(arr1);
    free(arr2);
    return 0;
}