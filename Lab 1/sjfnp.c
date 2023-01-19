#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int burstTime;
    int burstTimeRemaining;
    int arrTime;
    int pid;
    int entry;
    int exit;
    int inQueue;
    int isComplete;
} process;

void swap(process *a, process *b)
{
    process ta, tb;
    ta = *a;
    tb = *b;
    *b = ta;
    *a = tb;
}

void sort(process *processes, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].arrTime > processes[j].arrTime)
            {
                swap(&processes[i], &processes[j]);
            }
        }
    }
}

int front = -1, rear = -1, sz = 0;
process pq[500];

void pushQueue(process it)
{
    if (front == -1)
        front = 0;
    rear++;
    pq[rear] = it;
    sz++;
}

void popQueue()
{
    front++;
    sz--;
}

process queueFront()
{
    return pq[front];
}

int isEmpty()
{
    return sz == 0;
}

void SJF(process p[], int n)
{
    int time = 0, count = n;
    while (count)
    {
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrTime <= time && !p[i].inQueue && !p[i].isComplete)
            {
                pushQueue(p[i]);
                p[i].inQueue = 1;
            }
        }
        for (int i = front; i <= rear; i++)
            for (int j = front + 1; j <= rear; j++)
                if (pq[i].burstTime > pq[j].burstTime)
                    swap(&pq[i], &pq[j]);
        if (!isEmpty())
         {
            process currP = queueFront();
            popQueue();
            currP.entry = time;
            time += currP.burstTimeRemaining;
            currP.burstTimeRemaining = 0;
            currP.isComplete = 1;
            currP.inQueue = 0;
            currP.exit = time;
            count--;
            for (int i = 0; i < n; i++)
                if (currP.pid == p[i].pid)
                    p[i] = currP;
        }
    }
}

int main()
{ 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    process *p = (process *)malloc(n * sizeof(process));
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i;
        scanf("%d %d", &p[i].arrTime, &p[i].burstTime);
        p[i].entry = -1;
        p[i].exit = -1;
        p[i].inQueue = 0;
        p[i].isComplete = 0;
        p[i].burstTimeRemaining = p[i].burstTime;
    }

    sort(p, n);
    SJF(p, n);

    double waitTime = 0, turnTime = 0, resTime = 0;
    for (int i = 0; i < n; i++)
    {
        int tt = 0, wt = 0, rt = 0;
        tt = p[i].exit - p[i].arrTime;  // Turn Around time = Finish Time - Arrival Time
        wt = tt - p[i].burstTime;       // Waiting Time = Turn Around Time - Burst Time
        rt = p[i].entry - p[i].arrTime; // Response Time = Entry Time - Arrival Time
        waitTime += wt;
        turnTime += tt;
        resTime += rt;
    }

    printf("SJF Non Pre-emptive\n");
    printf("Average wait time: %.2f\n", waitTime / n);
    printf("Average response time: %.2f\n", resTime / n);
    printf("Average turnaround time: %.2f\n", turnTime / n);

    return 0;
}