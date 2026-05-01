#pragma once
#include "scheduler.h"
#include <algorithm>
#include <queue>
#include <vector>

class compare{
    public:
    bool operator()(const process &p1, const process &p2){
        if(p1.burstTime != p2.burstTime) return p1.burstTime > p2.burstTime;
        if(p1.arrivalTime != p2.arrivalTime) return p1.arrivalTime > p2.arrivalTime;
        return p1.id > p2.id;
    }
};

class sjfNonPreemptive : public Scheduler {
public:
    std::vector<process> runSimulation(std::vector<process> processes) override {
        std::priority_queue<process, std::vector<process>, compare> readyQueue;
        std::vector<process> completedProcesses;
        
        int currentTime = 0;
        int completedCount = 0;
        int n = processes.size();
        int i = 0; // Index to track which processes have arrived

        while (completedCount < n) {
            // 1. Move all processes that have arrived into the Ready Queue
            while (i < n && processes[i].arrivalTime <= currentTime) {
                readyQueue.push(processes[i]);
                i++;
            }

            // 2. If queue is empty, CPU is idle. Jump time forward.
            if (readyQueue.empty()) {
                currentTime = processes[i].arrivalTime;
                continue;
            }

            // 3. Execute the shortest job
            process currProcess = readyQueue.top();
            readyQueue.pop();

            timeline.push_back({currProcess.id, currentTime, currentTime+currProcess.burstTime});

            currProcess.waitingTime = currentTime - currProcess.arrivalTime;
            currentTime += currProcess.burstTime;
            currProcess.turnaroundTime = currProcess.waitingTime + currProcess.burstTime;
            currProcess.completionTime = currentTime;

            completedProcesses.push_back(currProcess);
            completedCount++;
        }

        return completedProcesses;
    }
};