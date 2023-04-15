#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
// Structure to store processes
struct Process {
    int pid; // Process ID
    int bt; // Burst Time
    int priority; // Priority of the process
};
// Function to sort the Processes acc. to priority
bool comparison(Process a, Process b) { 
    return (a.priority > b.priority); 
} 
// Function to find the waiting time for all processes 
void findWaitingTime(Process proc[], int n, int wt[]) { 
    // waiting time for first process is 0 
    wt[0] = 0; 
  
    // calculating waiting time 
    for (int i = 1; i < n; i++) { 
        wt[i] = proc[i - 1].bt + wt[i - 1]; 
    } 
} 

// Function to calculate turn around time 
void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) { 
    // calculating turnaround time by adding 
    // bt[i] + wt[i] 
    for (int i = 0; i < n; i++) { 
        tat[i] = proc[i].bt + wt[i]; 
    } 
} 
// Function to calculate average time 
void findavgTime(Process proc[], int n) { 
    int wt[n], tat[n], total_wt = 0, total_tat = 0; 
  
    // Function to find waiting time of all processes 
    findWaitingTime(proc, n, wt); 
  
    // Function to find turn around time for all processes 
    findTurnAroundTime(proc, n, wt, tat); 
  
    // Display processes along with all details 
    cout << "\nProcesses  " << " Burst time  " << " Waiting time  " << " Turn around time\n"; 
  
    // Calculate total waiting time and total turn around time 
    for (int i = 0; i < n; i++) { 
        total_wt = total_wt + wt[i]; 
        total_tat = total_tat + tat[i]; 
        cout << "   " << proc[i].pid << "\t\t" << proc[i].bt << "\t    " << wt[i] << "\t\t  " << tat[i] << endl; 
    } 
  
    cout << "\nAverage waiting time = " << (float)total_wt / (float)n; 
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
    cout<<endl; 
} 

// Function to implement Fixed Priority Preemptive Scheduling 
void fixedPriorityPreemptiveScheduling(Process proc[], int n) { 
    // Sort processes by priority 
    sort(proc, proc + n, comparison); 
  
    cout << "Order in which processes gets executed \n"; 
    for (int i = 0; i < n; i++) { 
        cout << proc[i].pid << " "; 
    } 
  
    findavgTime(proc, n); 
} 

// Function to implement Shortest Remaining Time First Scheduling 
void shortestRemainingTimeFirstScheduling(Process proc[], int n) { 
    // Sort processes by burst time 
    sort(proc, proc + n, comparison); 
  
    cout << "Order in which processes gets executed \n"; 
    for (int i = 0; i < n; i++) { 
        cout << proc[i].pid << " "; 
    } 
  
    findavgTime(proc, n); 
} 

// Function to implement Queue with two levels 
void queueWithTwoLevels(Process proc[], int n) { 
    // Queue 1 : Fixed priority preemptive Scheduling 
    // Queue 2 : Shortest Remaining Time First 
    int time = 0; 
  
    // Create two queues 
    queue<Process> q1; 
    queue<Process> q2; 
  
    // Push processes into Queue 1 
    for (int i = 0; i < n; i++) { 
        q1.push(proc[i]); 
    } 
  
    // Run loop until both queues are empty 
    while (!q1.empty() || !q2.empty()) { 
        // Check if Queue 1 is empty 
        if (!q1.empty()) { 
            Process curr = q1.front(); 
            q1.pop(); 
  
            // Check if the current process is completed 
            if (curr.bt <= 0) 
                continue; 
  
            // If remaining burst time is less than or equal to 2 
            if (curr.bt <= 2) { 
                time += curr.bt; 
                curr.bt = 0; 
            } 
  
            // If remaining burst time is greater than 2 
            else { 
                curr.bt -= 2; 
                time += 2; 
            } 
  
            // Push the current process back into Queue 1 
            q1.push(curr); 
        } 
  
        // If Queue 1 is empty, execute Queue 2 
        else { 
            Process curr = q2.front(); 
            q2.pop(); 
            if (curr.bt <= 0) 
                continue; 
            if (curr.bt <= 2) { 
                time += curr.bt; 
                curr.bt = 0; 
            } 
            else { 
                curr.bt -= 2; 
                time += 2; 
            } 
            q2.push(curr); 
        } 
    } 
  
    // Calculate average waiting and turn around times 
    findavgTime(proc, n); 
} 

// Driver code 
int main() { 
    // Processes with their burst time and priority 
    int a; 
    cout<<"Enter the number of processes:  ";
    cin>>a; 
    Process proc[a] = {}; 
    for(int i=0;i<a;i++){
    cout<<"Enter process id , burst time , piority :";
    cin>>proc[i].pid;
    cin>>proc[i].bt;
    cin>>proc[i].priority;
    }
    
    int n = sizeof(proc) / sizeof(proc[0]); 
  cout<<"first";

    // Queue with two levels 
    fixedPriorityPreemptiveScheduling(proc, n); 

    return 0; 
}