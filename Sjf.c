#include <stdio.h>

struct process {
    int id;    // Process ID
    int at;    // Arrival Time
    int bt;    // Burst Time
    int ct;    // Completion Time
    int tat;   // Turnaround Time
    int wt;    // Waiting Time
    int completed; // To track if the process is completed
};

int main() {
    int n;
    
    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n];
    int total_wt = 0, total_tat = 0;
    
    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, and Burst Time for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].id, &p[i].at, &p[i].bt);
        p[i].completed = 0;  // Mark all processes as incomplete
    }

    int time = 0, completed_processes = 0;
    
    // While not all processes are completed
    while (completed_processes < n) {
        int shortest_bt = 9999, idx = -1;
        
        // Find the process with the shortest burst time that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0 && p[i].bt < shortest_bt) {
                shortest_bt = p[i].bt;
                idx = i;
            }
        }

        // If no process is ready at the current time, move time forward
        if (idx == -1) {
            time++;
            continue;
        }

        // Process found, execute it
        time += p[idx].bt;
        p[idx].ct = time; // Completion time
        p[idx].tat = p[idx].ct - p[idx].at; // Turnaround time
        p[idx].wt = p[idx].tat - p[idx].bt; // Waiting time
        p[idx].completed = 1; // Mark process as completed
        
        total_wt += p[idx].wt;
        total_tat += p[idx].tat;

        completed_processes++;
        
        // Print Completion Time, Waiting Time, Turnaround Time for the current process
        printf("Process %d: CT = %d, WT = %d, TAT = %d\n", p[idx].id, p[idx].ct, p[idx].wt, p[idx].tat);
    }

    // Output average waiting time and total turnaround time
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Total Turnaround Time: %d\n", total_tat);

    return 0;
}
