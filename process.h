#pragma once
#include <ostream>

class process {

    public:

    // This allows us to onlytype: cout<< myProcess;
    friend std::ostream& operator<<(std::ostream& os, const process& p) {
        os << " " << p.id 
        << "  |    " << p.arrivalTime 
        << "    |  " << p.burstTime 
        << "    |    " << p.waitingTime 
        << "    |       " << p.turnaroundTime 
        << "    |      " << p.completionTime;
        return os;
    }

    int id; 
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int priority;
    
    process(int id, int at, int bt, int prio)
        : id(id),
          arrivalTime(at),
          burstTime(bt),
          remainingTime(bt),
          completionTime(0),
          turnaroundTime(0),
          waitingTime(0),
          priority(prio) {}
};

struct timeSlice {
    int processID;
    int startTime;
    int stopTime;
};