#include <iostream>
using namespace std;

// Process Node unit for the Linked List
struct Process
{
    int process_id;
    int execution_time;
    int remaining_time;
    Process *next;

    Process(int id, int exec_time)
    {
        process_id = id;
        execution_time = exec_time;
        remaining_time = exec_time;
        next = nullptr;
    }
};

// Scheduler class for scheduling. This is basically the Linked List for the Process Node units. It will contain the main logic of the program.
class Scheduler
{
private:
    Process *head;
    Process *tail;
    int time_per_process_per_cycle;

public:
    Scheduler(int time_per_process_per_cycle)
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->time_per_process_per_cycle = time_per_process_per_cycle;
    }

    // To Add process to the circular linked list
    void addProcess(int process_id, int execution_time)
    {
        Process *new_process = new Process(process_id, execution_time);
        if (!head)
        {
            head = tail = new_process;
            tail->next = head; // Making it a circular linked list
        }
        else
        {
            tail->next = new_process;
            tail = new_process;
            tail->next = head; // Maintain circularity
        }
    }

    // Remove a process from the circular linked list. We can just choose to ignore nodes but we will not be doing that.
    void removeProcess(Process *prev, Process *curr)
    {
        if (curr == head && curr == tail)
        { // Only one process left
            delete curr;
            head = tail = nullptr;
        }
        else
        {
            if (curr == head)
            {
                head = head->next;
            }
            prev->next = curr->next;
            if (curr == tail)
            {
                tail = prev;
            }
            delete curr;
        }
    }

    // Display current status of processes in the list. Main ne sir ke output ka chappa nahi mara. I made some small changes
    void displayProcesses()
    {
        if (!head)
        {
            cout << "No processes are running." << endl;
            return;
        }

        Process *temp = head;
        do
        {
            cout << "(P" << temp->process_id << ", Remaining: " << temp->remaining_time << ") ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    // Run the scheduler to assign CPU time to each process. This is the main logic of the program.
    void run()
    {
        if (!head)
        {
            cout << "No processes to schedule." << endl;
            return;
        }

        Process *curr = head;
        Process *prev = nullptr;

        while (head)
        {
            prev = nullptr;
            do
            {
                cout << "Running P" << curr->process_id << endl;

                if (curr->remaining_time <= time_per_process_per_cycle)
                {
                    // Process completes
                    cout << "P" << curr->process_id << " completes." << endl;
                    if (prev)
                    {
                        removeProcess(prev, curr);
                        curr = prev->next;
                    }
                    else
                    {
                        removeProcess(tail, curr);
                        curr = head;
                    }
                }
                else
                {
                    // Process doesn't complete, reduce its remaining time
                    curr->remaining_time -= time_per_process_per_cycle;
                    prev = curr;
                    curr = curr->next;
                }
                displayProcesses();
            } while (head && curr != head);
        }
    }

    // Add a new process during the scheduling
    void addNewProcess(int process_id, int execution_time)
    {
        cout << "New process arrives: P" << process_id << " (Remaining: " << execution_time << ")" << endl;
        addProcess(process_id, execution_time);
    }
};

// Main function to demonstrate the process scheduling
int main()
{
    // Create a scheduler with a time slice of 3 units
    Scheduler scheduler(3);

    // Adding initial processes
    scheduler.addProcess(1, 10);
    scheduler.addProcess(2, 5);
    scheduler.addProcess(3, 8);

    cout << "Initial Processes:" << endl;
    scheduler.displayProcesses();

    // Run the scheduler for the initial processes
    scheduler.run();

    // Dynamically add a new process after some cycles
    scheduler.addNewProcess(4, 9);

    // Continue running the scheduler with the new process
    scheduler.run();

    return 0;
}
