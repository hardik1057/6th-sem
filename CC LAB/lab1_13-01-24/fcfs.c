#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process
{
    int id, bt, at, ct, tat, wt;
};

// Function prototypes
void input(struct Process *p, int n);
void calc(struct Process *p, int n);
void sort(struct Process *p, int n);
void show(struct Process *p, int n);

int main()
{
    int n;
    printf("\nEnter the no of processes in your system:\n");
    scanf("%d", &n);

    struct Process *p = (struct Process*)malloc(n * sizeof(struct Process));
    struct Process f;

    input(p, n);
    sort(p, n);
    calc(p, n);
    show(p, n);

    free(p); // Release the allocated memory
    return 0;
}

// Function to take input for arrival and burst times for all processes
void input(struct Process *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter arrival time for process %d:\n", i + 1);
        scanf("%d", &p[i].at);
        printf("\nEnter burst time for process %d:\n", i + 1);
        scanf("%d", &p[i].bt);
        p[i].id = i + 1;
    }
}

// Function to calculate waiting, turn-around, and completion time
void calc(struct Process *p, int n)
{
    int sum = 0;
    sum = sum + p[0].at;

    for (int i = 0; i < n; i++)
    {
        sum = sum + p[i].bt;
        p[i].ct = sum;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        if (sum < p[i + 1].at && i + 1 < n)
        {
            int t = p[i + 1].at - sum;
            sum = sum + t;
        }
    }
}

// Function to sort processes with respect to arrival times
void sort(struct Process *p, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                // Swap burst times
                int temp = p[j].bt;
                p[j].bt = p[j + 1].bt;
                p[j + 1].bt = temp;

                // Swap arrival times
                temp = p[j].at;
                p[j].at = p[j + 1].at;
                p[j + 1].at = temp;

                // Swap IDs
                temp = p[j].id;
                p[j].id = p[j + 1].id;
                p[j + 1].id = temp;
            }
        }
    }
}

// Function to display process details
void show(struct Process *p, int n)
{
    printf("Process\tArrival\tBurst\tWaiting\tTurn Around\tCompletion\n");
    for (int i = 0; i < n; i++)
    {
        printf(" P[%d]\t %d\t%d\t%d\t %d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat, p[i].ct);
    }
}
