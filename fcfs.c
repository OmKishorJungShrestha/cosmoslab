//fcfs
#include <stdio.h>

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by arrival time
void sort_processes(int *bt, int *at, int *p, int n)
{
    int i, j;
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
}

// Function to calculate timings for the processes
void get_timings(int *bt, int *at, int *ct, int *tat, int *wt, int *p, int n)
{
    sort_processes(bt, at, p, n);

    ct[0] = bt[0] + at[0];
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

// Function to take inputs from the user
void get_inputs(int *p, int *at, int *bt, int n)
{int i;
    printf("Enter the details for %d processes:\n", n);
    for ( i = 0; i < n; i++)
    {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; // Assign process IDs
    }
}

// Function to print the table of process timings
void print_table(int *p, int *at, int *bt, int *ct, int *tat, int *wt, int n)
{int i;
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for ( i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}

// Function to print the Gantt chart
void print_gantt_chart(int *at, int *ct, int *p, int n)
{int i;
    printf("\nGantt Chart:\n");
    // Print the process sequence
    for ( i = 0; i < n; i++)
    {
        printf("| P%d ", p[i]);
    }
    printf("|\n");

    // Print the time line
    printf("0");
    for ( i = 0; i < n; i++)
    {
        printf("    %d", ct[i]);
    }
    printf("\n");
}

// Main function
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int p[n], bt[n], at[n];
    int ct[n], tat[n], wt[n];

    // Get inputs
    get_inputs(p, at, bt, n);

    // Calculate timings
    get_timings(bt, at, ct, tat, wt, p, n);

    // Print the table and Gantt chart
    print_table(p, at, bt, ct, tat, wt, n);
    print_gantt_chart(at, ct, p, n);

    return 0;
}
