#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

// Function to perform Round Robin Scheduling
void roundRobinScheduling(struct Process processes[], int n, int timeQuantum) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes
    int waitingTime[n], turnaroundTime[n];

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                // Execute the process for the time quantum or remaining time, whichever is smaller
                int executionTime = (processes[i].remainingTime < timeQuantum) ? processes[i].remainingTime : timeQuantum;
                processes[i].remainingTime -= executionTime;
                time += executionTime;

                // If the process is completed
                if (processes[i].remainingTime == 0) {
                    completed++;
                    waitingTime[i] = time - processes[i].arrivalTime - processes[i].burstTime;
                    turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
                }
            }
        }
    }

    // Calculate and display average times and schedule
    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += waitingTime[i];
        avgTurnaroundTime += turnaroundTime[i];
    }

    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    int n;
    int timeQuantum;

    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Get the time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;

        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);

        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    // Perform Round Robin Scheduling
    roundRobinScheduling(processes, n, timeQuantum);

    return 0;
}
