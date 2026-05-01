#include<iostream>
#include "process.h"
#include "fcfs.h"
#include "sjfNonPreemptive.h"
#include "simulator.h"
#include "utility.h"
#include "roundRobin.h"
#include "srtf.h"
#include "priorityNonPreemptive.h"


int main(){
    std::vector<process>processes;
    
    int numberOfProcesess;
    std::cout << "Enter the number of processes : ";
    std::cin >> numberOfProcesess;

    for(int i=0; i<numberOfProcesess; i++){

        int process_id, arrival, burst, prio;

        std::cout << "\nEnter required details for process " << i+1 << '\n';
        std::cout << "Enter the process id : ";
        std::cin >> process_id;

        std::cout << "Enter the arrival time : ";
        std::cin >> arrival;

        std::cout << "Enter the burst time : ";
        std::cin >> burst;

        std::cout << "Enter the priority : ";
        std::cin >> prio;

        processes.push_back(process(process_id,arrival,burst,prio));

    }

    Scheduler *FCFS = new fcfs();
    simulator fcfsSim(processes, FCFS);
    std::vector<process>fcfsResults = fcfsSim.start();
    std::cout << "\n============ FCFS ============\n";
    printProcessTable(fcfsResults);
    printGanttChart(FCFS->getTimeline());
    delete(FCFS);

    Scheduler *sjfnon = new sjfNonPreemptive();
    simulator sjfnonSim(processes, sjfnon);
    std::vector<process>sjfnonResults = sjfnonSim.start();
    std::cout << "\n============ SJF Non Preemptive ============\n";
    printProcessTable(sjfnonResults);
    printGanttChart(sjfnon->getTimeline());
    delete(sjfnon);

    Scheduler *roundrobin = new roundRobin(2);
    simulator simRoundRobin(processes, roundrobin);
    std::vector<process>resultRoundRobin = simRoundRobin.start();
    std::cout << "\n============ Round Robin ============\n";
    printProcessTable(resultRoundRobin);
    printGanttChart(roundrobin->getTimeline());
    delete(roundrobin);

    Scheduler *SRTF = new srtf();
    simulator simSRTF(processes, SRTF);
    std::vector<process>resultSRTF = simSRTF.start();
    std::cout << "\n============ SRTF ============\n";
    printProcessTable(resultSRTF);
    printGanttChart(SRTF->getTimeline());
    delete(SRTF);
    
    Scheduler *Priority = new priorityNonPreemptive();
    simulator simPriority(processes, Priority);
    std::vector<process>resultPrio = simPriority.start();
    std::cout << "\n============ Priority Scheduling ============\n";
    printProcessTable(resultPrio);
    printGanttChart(Priority->getTimeline());
    delete(Priority);

    return 0;
}