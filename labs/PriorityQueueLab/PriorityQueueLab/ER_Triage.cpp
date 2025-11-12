// ER_Triage.cpp
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

struct Patient 
{
    std::string name;
    int priority;

    bool operator<(const Patient& other) const 
    {
        return priority < other.priority; // max-heap
    }
};

class TriageQueue 
{
private:
    std::priority_queue<Patient> heap;

public:
    void Enqueue(const Patient& patient) 
    {
        // insert the patient into the queue
        heap.push(patient);
        
        // Call visualize to display and log the entire queue
    }

    Patient Dequeue() 
    {
        // if the queue is empty throw an exception
        
        // Display and log the patient treated and their priority
        
        // Call visualize to display and log the entire queue
        
        // Return the dequeued patient
    }

    Patient Peek() const 
    {
        // Return the patient at the root or throw exception if the heap is empty
    }
	
	bool IsEmpty() const 
    {
		return heap.empty();
	}

    void Visualize() const 
    {
        // Print the contents of the current priority queue
        // to both the display and the log file
    }

    void LoadFromFile(const std::string& filename) 
    {
        std::ifstream file(filename);
        std::string line;
        while (getline(file, line)) 
        {
            std::istringstream iss(line);
            std::string name;
            int priority;
            if (iss >> name >> priority)
                Enqueue({name, priority});
        }
    }
};

int main() 
{
    TriageQueue triage;
    triage.LoadFromFile("patients.txt");
    
	while (!triage.IsEmpty()) 
    {
		cout << triage.Peek().name << endl;
		triage.Dequeue();
	}	
	
    return 0;
}
