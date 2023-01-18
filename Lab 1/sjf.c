#include <stdio.h>

#define maxProcess 10

int main()
{
    char pn[maxProcess][maxProcess];
    int a[maxProcess], b[maxProcess], x[maxProcess];
    int smallest, count = 0, time, n;
    int waiting[maxProcess], turnaround[maxProcess], completion[maxProcess], response[maxProcess];
    float wt = 0, tt = 0, rt = 0, end;
    printf("Enter the number of processes to schedule: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter the process name, arrival time and burst time for each process: ");
        scanf("%s %d %d", pn[i], &a[i], &b[i]);
    }

    for (int i = 0; i < n; i++)
        x[i] = b[i];

    b[maxProcess - 1] = 10000;

    for (time = 0; count != n; time++)
    {
        smallest = maxProcess - 1;
        for (int i = 0; i < n; i++)
            if (a[i] <= time && b[i] < b[smallest] && b[i] > 0)
                smallest = i;
        if (b[smallest] == x[smallest])
            response[smallest] = time - a[smallest];
        b[smallest]--;
        if (b[smallest] == 0)
        {
            count++;
            end = time + 1;
            completion[smallest] = end;
            waiting[smallest] = end - a[smallest] - x[smallest];
            turnaround[smallest] = end - a[smallest];
        }
    }
    printf("\nProcess\t\tburst-time\tarrival-time\twaiting-time\tturnaround-time\tcompletion-time\n");
    printf("-------\t\t----------\t------------\t------------\t---------------\t---------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("\n%s\t\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pn[i], x[i], a[i], waiting[i], turnaround[i], completion[i]);
        wt += waiting[i];
        tt += turnaround[i];
        rt += response[i];
    }

    printf("\n\nAverage waiting time = %.2f\n", wt / n);
    printf("Average Turnaround time = %.2f\n", tt / n);
    printf("Average response time: %.2f\n\n", rt / n);

    return 0;
}