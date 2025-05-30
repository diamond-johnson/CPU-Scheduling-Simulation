#include "scheduler.h"
#include <stdlib.h>

// ---------------- Scheduling Algorithms ----------------

// FCFS Scheduling
Metrics fcfs_metrics(Process proc[], int n) {
    int totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;
    int completionTime = 0;

    for (int i = 0; i < n; i++) {
        if (completionTime < proc[i].arrivalTime) {
            completionTime = proc[i].arrivalTime;
        }
        completionTime += proc[i].burstTime;
        proc[i].completionTime = completionTime;
        int turnaround = proc[i].completionTime - proc[i].arrivalTime;
        int waiting = turnaround - proc[i].burstTime;

        totalTurnaround += turnaround;
        totalWaiting += waiting;
        totalResponse += waiting; // Response time equals waiting for FCFS
    }

    Metrics metrics;
    metrics.avgTurnaround = (float)totalTurnaround / n;
    metrics.avgWaiting = (float)totalWaiting / n;
    metrics.avgResponse = (float)totalResponse / n;

    return metrics;
}

// SJF Scheduling (Non-preemptive)
Metrics sjf_metrics(Process proc[], int n) {
    int totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;
    int completed = 0, currentTime = 0;
    int isCompleted[1000] = {0}; // assume n<=1000

    while(completed < n){
        int idx = -1;
        int minBurst = 1e9;
        for(int i=0; i<n; i++){
            if(proc[i].arrivalTime <= currentTime && !isCompleted[i]){
                if(proc[i].burstTime < minBurst){
                    minBurst = proc[i].burstTime;
                    idx = i;
                } else if(proc[i].burstTime == minBurst){
                    if(proc[i].arrivalTime < proc[idx].arrivalTime)
                        idx = i;
                }
            }
        }
        if(idx != -1){
            currentTime += proc[idx].burstTime;
            proc[idx].completionTime = currentTime;
            int turnaround = proc[idx].completionTime - proc[idx].arrivalTime;
            int waiting = turnaround - proc[idx].burstTime;

            totalTurnaround += turnaround;
            totalWaiting += waiting;
            totalResponse += waiting; // same as waiting for non-preemptive

            isCompleted[idx] = 1;
            completed++;
        } else {
            currentTime++;
        }
    }

    Metrics metrics;
    metrics.avgTurnaround = (float)totalTurnaround / n;
    metrics.avgWaiting = (float)totalWaiting / n;
    metrics.avgResponse = (float)totalResponse / n;

    return metrics;
}

// Round Robin Scheduling (corrected)
Metrics rr_metrics(Process proc[], int n, int timeQuantum) {
    int totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;
    int remainingTime[1000];
    int firstResponseTime[1000];
    int isCompleted[1000] = {0};
    int completed = 0;
    int currentTime = 0;
    int i;

    for(i=0; i<n; i++){
        remainingTime[i] = proc[i].burstTime;
        firstResponseTime[i] = -1;
    }

    int processQueue[1000];
    int front = 0, rear = 0;

    for(i=0; i<n; i++){
        if(proc[i].arrivalTime <= currentTime){
            processQueue[rear++] = i;
        }
    }

    while(completed < n){
        if(front == rear){
            int nextArrival = 1e9;
            for(i=0; i<n; i++){
                if(!isCompleted[i] && proc[i].arrivalTime > currentTime){
                    if(proc[i].arrivalTime < nextArrival){
                        nextArrival = proc[i].arrivalTime;
                    }
                }
            }
            currentTime = nextArrival;
            for(i=0; i<n; i++){
                if(proc[i].arrivalTime <= currentTime && !isCompleted[i]){
                    processQueue[rear++] = i;
                }
            }
            continue;
        }

        int idx = processQueue[front++];

        if(firstResponseTime[idx] == -1){
            firstResponseTime[idx] = currentTime;
        }

        if(remainingTime[idx] > timeQuantum){
            remainingTime[idx] -= timeQuantum;
            currentTime += timeQuantum;
        } else {
            currentTime += remainingTime[idx];
            remainingTime[idx] = 0;
            proc[idx].completionTime = currentTime;
            int turnaround = proc[idx].completionTime - proc[idx].arrivalTime;
            int waiting = turnaround - proc[idx].burstTime;

            totalTurnaround += turnaround;
            totalWaiting += waiting;
            totalResponse += (firstResponseTime[idx] - proc[idx].arrivalTime);

            isCompleted[idx] = 1;
            completed++;
        }

        for(i=0; i<n; i++){
            if(proc[i].arrivalTime <= currentTime && !isCompleted[i]){
                int inQueue = 0;
                for(int j=front; j<rear; j++){
                    if(processQueue[j] == i){
                        inQueue = 1; break;
                    }
                }
                if(!inQueue && i != idx){
                    processQueue[rear++] = i;
                }
            }
        }

        if(!isCompleted[idx] && remainingTime[idx] > 0){
            processQueue[rear++] = idx;
        }
    }

    Metrics metrics;
    metrics.avgTurnaround = (float)totalTurnaround / n;
    metrics.avgWaiting = (float)totalWaiting / n;
    metrics.avgResponse = (float)totalResponse / n;

    return metrics;
}

