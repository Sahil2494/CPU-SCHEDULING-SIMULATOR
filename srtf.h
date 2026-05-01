#pragma once
#include "scheduler.h"
#include<queue>
#include<vector>

class comparesrtf{
    public:
    //return true if p1 should get less priority
    bool operator()(const process &p1, const process &p2){
        if(p1.remainingTime==p2.remainingTime) return p1.id > p2.id;
        else return p1.remainingTime > p2.remainingTime;
    }
};

class srtf : public Scheduler{
    public:
    std::vector<process> runSimulation(std::vector<process> processes) override {
        std::priority_queue<process, std::vector<process>, comparesrtf> readyQueue;
        std::vector<process> completedProcesses;

        if(processes.size() == 0) return completedProcesses;

        int currTime = processes[0].arrivalTime;
        int i = 0;

        // Loop until all processes have arrived AND the queue is completely empty
        while(i < processes.size() || !readyQueue.empty()){
            
            //Push all processes that have arrived up to the current time
            while(i < processes.size() && processes[i].arrivalTime <= currTime){
                readyQueue.push(processes[i++]);
            }

            //Idle CPU check 
            if(readyQueue.empty() && i < processes.size()){
                currTime = processes[i].arrivalTime;
                continue; // Jump to the next arrival without popping
            }

            process currProcess = readyQueue.top();
            readyQueue.pop();

            if (!timeline.empty() && timeline.back().processID == currProcess.id) {
                timeline.back().stopTime = currTime + 1;
            } else {
                timeline.push_back({currProcess.id, currTime, currTime + 1});
            }

            currProcess.remainingTime--;
            currTime++;

            if (currProcess.remainingTime == 0) {
                currProcess.completionTime = currTime;
                currProcess.turnaroundTime = currProcess.completionTime - currProcess.arrivalTime;
                currProcess.waitingTime = currProcess.turnaroundTime - currProcess.burstTime;
                completedProcesses.push_back(currProcess);
            } else {
                readyQueue.push(currProcess);
            }
        }

        return completedProcesses;
    }
};