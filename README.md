# 🖥️ CPU Scheduling Simulator

A zero-dependency, optimized CPU Scheduling Simulator built entirely in native C++. 

This project simulates the behavior of a multi-programmed operating system's CPU scheduler. It features a completely self-contained Command Line Interface (CLI) that calculates process execution metrics and dynamically renders Gantt charts directly to the terminal.
I am thinking of adding good UI, as terminal may seem trivial. Sugestions are welcome.

## 🚀 Key Features
* **Zero Dependencies:** Pure C++ implementation requiring no external libraries..
* **Native Terminal UI:** Dynamically generates Gantt charts and formatted statistical tables for each scheduling algorithm.
* **Object-Oriented Design:** Architected using the **Strategy Design Pattern** to ensure highly decoupled and scalable algorithm execution.

## ⚙️ Implemented Algorithms
1. **First Come First Serve (FCFS)**
2. **Shortest Job First (SJF)** - *Non-Preemptive*
3. **Shortest Remaining Time First (SRTF)** - *Preemptive*
4. **Round Robin (RR)** - *Configurable Time Quantum* (hardcoded here, can be amended by the client)
5. **Priority Scheduling** - *Non-Preemptive*

## 🏗️ System Architecture & Low-Level Design (LLD)
The system is built with adherence to SOLID principles, specifically utilizing polymorphism to manage the algorithms.

* `Scheduler` (Base Class): Defines the contract `runSimulation()` and encapsulates the `timeline` state vector.
* `Concrete Strategies` (`fcfs.h`, `roundRobin.h`, etc.): Implement the specific queueing and execution logic.
* `Simulator` (Context Wrapper): Handles process pre-sorting and dynamically injects the chosen algorithm at runtime, completely decoupling the business logic from the file execution.

## 🛠️ Installation & Execution

This project can be compiled with any standard C++ compiler (GCC, Clang, MSVC).

**1. Clone the repository**
```bash
git clone [https://github.com/yourusername/CPU-Scheduling-Simulator.git](https://github.com/yourusername/CPU-Scheduling-Simulator.git)
cd CPU-Scheduling-Simulator
```

**2. Compile the source code**
```bash
g++ main.cpp -o simulate
```

**3. Run the application**
```bash
.\simulate
```

**Output**

<img width="934" height="904" alt="s1" src="https://github.com/user-attachments/assets/46d83465-45bc-4221-ae78-bfdb84768fb3" />
<img width="705" height="913" alt="s2" src="https://github.com/user-attachments/assets/ef82123a-f86e-4c06-a1d9-ca07b03d8336" />
<img width="294" height="161" alt="s3" src="https://github.com/user-attachments/assets/347ac0f4-c261-442c-acb4-cf770ecf0a74" />

