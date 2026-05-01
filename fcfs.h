#pragma once
#include "scheduler.h"

class fcfs : public Scheduler{
    public:
        std::vector<process> runSimulation(std::vector<process>readyQueue) override{
            std::vector<process>completedProcesses;
            int currTime = 0;
            for(int i=0; i<readyQueue.size(); i++){

                if(currTime < readyQueue[i].arrivalTime) currTime = readyQueue[i].arrivalTime;

                readyQueue[i].waitingTime = currTime - readyQueue[i].arrivalTime;

                timeline.push_back({readyQueue[i].id, currTime, currTime+readyQueue[i].burstTime});
                currTime += readyQueue[i].burstTime;
                readyQueue[i].turnaroundTime = readyQueue[i].waitingTime+readyQueue[i].burstTime;
                readyQueue[i].completionTime = currTime;

                completedProcesses.push_back(readyQueue[i]);
            }
            return completedProcesses;
        }
};