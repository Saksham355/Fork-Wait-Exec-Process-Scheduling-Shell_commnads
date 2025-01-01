#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void search(int arr[], int s, int e, int target) // Recursive binary search algorithm.
{
    if (s > e)
    {
        printf("-1\n");
        exit(0);
    }
    int m = s + (e - s) / 2;
    if (arr[m] == target)
    {
        printf("Target index:%d\n", m);
        exit(0);
    }
    int r = fork(); // New child created which takes half of the array and runs binary search on it.
    if (r == 0)
    {
        if (arr[m] > target)
        {
            search(arr, s, m - 1, target);
        }
        else
        {
            search(arr, m + 1, e, target);
        }
    }
    else
    {
        wait(NULL); // Parent process waits for the child process to terminate.
        exit(0);
    }
}
int main() // Main program to take target index and print the resulting index in the fixed array.
{
    int arr[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int target = 13;
    printf("Array: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Enter the target value: ");
    scanf("%d", &target);
    search(arr, 0, 15, target);
    return 0;
}
