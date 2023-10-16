#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
};

// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    waitingTime[0] = 0; // Waiting time for the first process is 0

    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }
}

// Function to calculate average waiting time and average turnaround time
void calculateAverages(struct Process processes[], int n) {
    int waitingTime[n], turnaroundTime[n];

    calculateTimes(processes, n, waitingTime, turnaroundTime);

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

// Function to display the schedule
void displaySchedule(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    printf("ProcessID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime,
               processes[i].burstTime, waitingTime[i], turnaroundTime[i]);
    }
}

// Function to perform Non-Preemptive SJF Scheduling
void nonPreemptiveSJF(struct Process processes[], int n) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes
    int waitingTime[n], turnaroundTime[n];

    // Sort processes based on burst time (Shortest Job First)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burstTime > processes[j + 1].burstTime) {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    while (completed < n) {
        if (processes[completed].arrivalTime <= time) {
            // Process is ready for execution
            waitingTime[completed] = time - processes[completed].arrivalTime;
            turnaroundTime[completed] = waitingTime[completed] + processes[completed].burstTime;
            time += processes[completed].burstTime;
            completed++;
        } else {
            // No process is ready, move to the next arrival time
            time++;
        }
    }

    // Calculate and display average times and schedule
    calculateAverages(processes, n);
    displaySchedule(processes, n, waitingTime, turnaroundTime);
}

int main() {
    int n;

    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;

        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);

        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    // Perform Non-Preemptive SJF Scheduling
    nonPreemptiveSJF(processes, n);

    return 0;
}
