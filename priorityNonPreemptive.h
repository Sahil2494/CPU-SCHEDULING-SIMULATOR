#pragma once
#include "scheduler.h"
#include <queue>
#include <vector>

// Comparator: Sorts by Priority first, then falls back to Arrival Time (FCFS)
struct comparePriority {
    bool operator()(const process &p1, const process &p2) {
        //If priorities are same, the one that arrived first wins
        if (p1.priority == p2.priority) {
            if(p1.arrivalTime==p2.arrivalTime) return p1.id > p2.id;
            return p1.arrivalTime > p2.arrivalTime;
        }
        //lower Number = higher priority
        return p1.priority > p2.priority; 
    }
};

class priorityNonPreemptive : public Scheduler {
public:
    std::vector<process> runSimulation(std::vector<process> processes) override {
        std::priority_queue<process, std::vector<process>, comparePriority> readyQueue;
        std::vector<process> completedProcesses;
        
        int currentTime = 0;
        int completedCount = 0;
        int n = processes.size();
        int i = 0;

        while (completedCount < n) {
            // pushing all arrived processes into the queue
            while (i < n && processes[i].arrivalTime <= currentTime) {
                readyQueue.push(processes[i]);
                i++;
            }

            //idle CPU Check
            if (readyQueue.empty()) {
                if (i < n) currentTime = processes[i].arrivalTime;
                continue;
            }

            // popping the highest priority process (lowest integer)
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