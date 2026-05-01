#pragma once
#include "process.h"
#include "scheduler.h"
#include <algorithm>
#include <vector>

class simulator {
private:
    std::vector<process> arrivalPool;
    Scheduler* algorithmType;

public:
    simulator(std::vector<process>& processes, Scheduler* algo) 
        : arrivalPool(processes), algorithmType(algo) {
        
        //sort by arrival time
        std::sort(arrivalPool.begin(), arrivalPool.end(), [](const process& a, const process& b) {
            if (a.arrivalTime == b.arrivalTime) return a.id < b.id;
            return a.arrivalTime < b.arrivalTime;
        });
        
    }

    std::vector<process> start() {
        return algorithmType->runSimulation(arrivalPool); 
    }
};