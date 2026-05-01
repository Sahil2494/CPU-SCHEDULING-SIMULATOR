#pragma once
#include "scheduler.h"
#include <queue>
class roundRobin : public Scheduler{
    public:
    int timeQuantum;
    
    roundRobin(int quantum):timeQuantum(quantum){
        if (quantum<=0) timeQuantum = 2;//default
    }

    std::vector<process> runSimulation(std::vector<process>processes) override {
        int currTime = 0;
        std::vector<process>completedProcesses;

        std::queue<process>readyQueue;

        int i = 0;
        if(processes.size()==0) return completedProcesses;
        currTime = processes[i].arrivalTime;
        readyQueue.push(processes[i++]); //assuming atleast one element is there

        while(!readyQueue.empty()){

            process p = readyQueue.front();
            readyQueue.pop();
            
            int timeRan = std::min(timeQuantum, p.remainingTime);
            int start = currTime; //label start
            currTime += timeRan;
            int end = currTime; //label stop

            timeline.push_back({p.id,start,end});

            p.remainingTime -= timeRan;

            if(p.remainingTime==0){
                p.turnaroundTime = currTime - p.arrivalTime;
                p.waitingTime = p.turnaroundTime - p.burstTime;
                p.completionTime = currTime;
                completedProcesses.push_back(p);
            }

            while(i<processes.size() && processes[i].arrivalTime<=currTime){
                readyQueue.push(processes[i++]);
            }

            if(p.remainingTime>0){
                readyQueue.push(p);
            }

            if(readyQueue.empty() && i<processes.size()){
                currTime = processes[i].arrivalTime;
                readyQueue.push(processes[i++]);
            }

        }
        return completedProcesses;
    }

};