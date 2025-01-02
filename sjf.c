//sjf
#include <stdio.h>

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by arrival time and then by burst time
void sort_processes(int *bt, int *at, int *p, int n)
{
    int i, j;

    // Sort by arrival time
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                swap(&at[j], &at[j + 1]);
                swap(&bt[j], &bt[j + 1]);
                swap(&p[j], &p[j + 1]);
            }
        }
    }

    // Sort by burst time for processes with the same arrival time
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (at[j] == at[j + 1] && bt[j] > bt[j + 1])
            {
                swap(&at[j], &at[j + 1]);
                swap(&bt[j], &bt[j + 1]);
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

// Function to calculate completion, turnaround, and waiting times
void get_timings(int *bt, int *at, int *ct, int *tat, int *wt, int *p, int n)
{
    sort_processes(bt, at, p, n);

    ct[0] = at[0] + bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = tat[0] - bt[0];
int i;
    for ( i = 1; i < n; i++)
    {
        // Calculate the completion time of the current process
        if (at[i] > ct[i - 1])
        {
            ct[i] = at[i] + bt[i];
        }
        else
        {
            ct[i] = ct[i - 1] + bt[i];
        }

        // Calculate turnaround time and waiting time
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}

// Function to print process table
void print_table(int *p, int *at, int *bt, int *ct, int *tat, int *wt, int n)
{int i;
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for ( i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}

// Function to print the Gantt chart
void print_gantt_chart(int *at, int *ct, int *p, int n)
{
    printf("Gantt Chart:\n");
    // Print process sequence
    int i;
    for ( i = 0; i < n; i++)
    {
        printf("| P%d ", p[i]);
    }
    printf("|\n");

    // Print timeline
    printf("%d", at[0]);
    for ( i = 0; i < n; i++)
    {
        printf("    %d", ct[i]);
    }
    printf("\n");
}

// Function to print average times
void print_average_times(int *tat, int *wt, int n)
{int i;
    float avg_tat = 0, avg_wt = 0;

    for ( i = 0; i < n; i++)
    {
        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
}

int main()
{
    int n,i;

    // Get number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int p[n], at[n], bt[n], ct[n], tat[n], wt[n];

    // Get arrival times and burst times
    printf("Enter the Arrival Time and Burst Time for each process:\n");
    for ( i = 0; i < n; i++)
    {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; // Assign process ID
    }

    // Calculate timings
    get_timings(bt, at, ct, tat, wt, p, n);

    // Print process table
    printf("\nProcess Table:\n");
    print_table(p, at, bt, ct, tat, wt, n);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    print_gantt_chart(at, ct, p, n);

    // Print average times
    printf("\nAverage Times:\n");
    print_average_times(tat, wt, n);

    return 0;
}
