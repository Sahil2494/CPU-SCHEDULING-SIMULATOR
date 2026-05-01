#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "process.h"
#include "utility.h"

class Scheduler {
    protected:
    std::vector<timeSlice>timeline;
public:
    virtual std::vector<process> runSimulation(std::vector<process> processes) = 0;
    virtual ~Scheduler() = default;
    std::vector<timeSlice> getTimeline() const {
        return timeline;
    }
};
