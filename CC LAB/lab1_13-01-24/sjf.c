#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
} ps[100];

int main()
{

    int n;
    bool is_completed[100] = {false};
    bool is_first_process = true;
    int current_time = 0;
    int completed = 0;
    ;
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    float sum_tat = 0, sum_wt = 0;
    int prev = 0;
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Arrival Time: ", i);
        scanf("%d", &ps[i].at);
        ps[i].pid = i;
    }
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Burst Time: ", i);
        scanf("%d", &ps[i].bt);
    }
    while (completed != n)
    {

        int min_index = -1;
        int minimum = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && is_completed[i] == false)
            {
                if (ps[i].bt < minimum)
                {
                    minimum = ps[i].bt;
                    min_index = i;
                }
                if (ps[i].bt == minimum)
                {
                    if (ps[i].at < ps[min_index].at)
                    {
                        minimum = ps[i].bt;
                        min_index = i;
                    }
                }
            }
        }

        if (min_index == -1)
        {
            current_time++;
        }
        else
        {
            ps[min_index].start_time = current_time;
            ps[min_index].ct = ps[min_index].start_time + ps[min_index].bt;
            ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
            ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;

            ps[min_index].rt = ps[min_index].start_time - ps[min_index].at;

            sum_tat += ps[min_index].tat;
            sum_wt += ps[min_index].wt;

            if (is_first_process == true)
                printf("CPU idle time=0");
            else
            {
                int l = (ps[min_index].start_time - prev);
                printf("\nCPU idle time= %d", l);
            }
            completed++;
            is_completed[min_index] = true;
            current_time = ps[min_index].ct;
            prev = current_time;
            is_first_process = false;
        }
    }
    printf("\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    printf("\n");
    printf("\nAverage Turn Around time= %f ", sum_tat / n);
    printf("\nAverage Waiting Time= %f ", sum_wt / n);
    return 0;
}
