#pragma once
#include <vector>
#include <iostream>
#include <iomanip> // Required for std::setw and table formatting
#include "process.h"

// ---------------------------------------------------------
// 1. Tabular Representation of Process Details
// ---------------------------------------------------------
inline void printProcessTable(const std::vector<process>& completed) {
    if (completed.empty()) {
        std::cout << "No processes to display.\n";
        return;
    }

    float totalTAT = 0, totalWT = 0;

    std::cout << "\n=== PROCESS SCHEDULING STATISTICS ===\n";
    std::cout << "+" << std::string(47, '-') << "+\n";
    std::cout << "| " 
              << std::setw(5) << std::left << "PID" << " | "
              << std::setw(5) << std::left << "AT"  << " | "
              << std::setw(5) << std::left << "BT"  << " | "
              << std::setw(5) << std::left << "CT"  << " | "
              << std::setw(5) << std::left << "TAT" << " | "
              << std::setw(5) << std::left << "WT"  << " |\n";
    std::cout << "+" << std::string(47, '-') << "+\n";

    for (const auto& p : completed) {
        std::cout << "| " 
                  << "P" << std::setw(4) << std::left << p.id << " | "
                  << std::setw(5) << std::left << p.arrivalTime << " | "
                  << std::setw(5) << std::left << p.burstTime << " | "
                  << std::setw(5) << std::left << p.completionTime << " | "
                  << std::setw(5) << std::left << p.turnaroundTime << " | "
                  << std::setw(5) << std::left << p.waitingTime << " |\n";
        
        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
    }
    
    std::cout << "+" << std::string(47, '-') << "+\n";
    
    // Print Averages
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Turnaround Time: " << (totalTAT / completed.size()) << "\n";
    std::cout << "Average Waiting Time:    " << (totalWT / completed.size()) << "\n\n";
}

// ---------------------------------------------------------
// 2. ASCII Gantt Chart Representation
// ---------------------------------------------------------
inline void printGanttChart(const std::vector<timeSlice>& timeline) {
    if (timeline.empty()) {
        std::cout << "Timeline is empty. Nothing to display.\n";
        return;
    }

    std::cout << "=== GANTT CHART ===\n\n";

    // 1. Print Top Border
    std::cout << " ";
    for (size_t i = 0; i < timeline.size(); i++) {
        std::cout << "------- ";
    }
    std::cout << "\n";

    // 2. Print Process IDs in the middle of blocks
    std::cout << "|";
    for (const auto& slice : timeline) {
        // Adjust spacing if PID is double digits to keep boxes uniform
        if (slice.processID < 10) std::cout << "  P" << slice.processID << "   |";
        else std::cout << " P" << slice.processID << "   |";
    }
    std::cout << "\n";

    // 3. Print Bottom Border
    std::cout << " ";
    for (size_t i = 0; i < timeline.size(); i++) {
        std::cout << "------- ";
    }
    std::cout << "\n";

    // 4. Print Timeline Numbers
    std::cout << timeline[0].startTime;
    for (const auto& slice : timeline) {
        // Calculate spacing to keep numbers aligned under the '|' dividers
        std::string stopStr = std::to_string(slice.stopTime);
        int spaces = 8 - stopStr.length();
        
        for (int s = 0; s < spaces; s++) std::cout << " ";
        std::cout << slice.stopTime;
    }
    std::cout << "\n\n";
}