# CPU Scheduling Simulation
This project implements three fundamental CPU scheduling algorithms in C.

# Algorithms Implemented:
1. FCFS (First Come First Serve)
2. SJF (Shortest Job First - Non-Preemptive)
3.  Round Robin (RR)
# Performance Metrics
Each algorithm computes the following performance metrics:
1. Average Turnaround Time: The total time taken from arrival to completion for each process.
2. Average Waiting Time: The total time a process has been in the ready queue.
3. Average Response Time: The time from arrival until the first response (for non-preemptive algorithms, this is the same as waiting time).
# How to Run the Code 
1. Compile the Code: Open a terminal and navigate to the project directory.
Use the following command to compile the code:
```make ```
2. Run the Test Cases: After compiling, run the test cases using:
```make run ```
3. Clean Up: To remove compiled files, use:
```make clean ```
# Inputs and Outputs 
Inputs: The program uses predefined test cases within the scheduler_test.c file. Each test case consists of an array of processes, where each process has:
pid: Process ID 
arrivalTime: Time at which the process arrives 
burstTime: Time required for the process to complete  

Outputs: The program outputs the calculated and expected values for average turnaround time, waiting time, and response time for each scheduling algorithm.

Sample Output for Each Algorithm 
Test Case 1 
``` ==== Test Case 1 ==== FCFS: Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33       Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33 SJF:  Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33       Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33 RR (Quantum = 4): Calculated: Turnaround: 19.33, Waiting: 11.67, Response: 3.00          Expected:   Turnaround: 19.33, Waiting: 11.67, Response: 3.00 >>> Test Case 1 PASSED. ```  
Test Case 2 
``` ==== Test Case 2 ==== FCFS: Calculated: Turnaround: 5.67, Waiting: 1.67, Response: 1.67       Expected:   Turnaround: 5.67, Waiting: 1.67, Response: 1.67 SJF:  Calculated: Turnaround: 5.67, Waiting: 1.67, Response: 1.67       Expected:   Turnaround: 5.67, Waiting: 1.67, Response: 1.67 RR (Quantum = 2): Calculated: Turnaround: 5.67, Waiting: 1.67, Response: 1.00          Expected:   Turnaround: 5.67, Waiting: 1.67, Response: 1.00 >>> Test Case 2 PASSED. ```
