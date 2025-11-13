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
    ostream* logStream = nullptr;
    void Print(const std::string& message) const 
    {
        std::cout << message << endl;
        if (logStream)
            (*logStream) << message << endl;
    }

public:
    void Enqueue(const Patient& patient) 
    {
        heap.push(patient);
        Visualize();
    }

    void SetLogStream(ostream* stream)
    {
        logStream = stream;
    }

    Patient Dequeue() 
    {
        // if the queue is empty throw an exception
        if (heap.empty())
            throw out_of_range("Error: The Triage is Empty");

        Patient treated = heap.top();
        heap.pop();

        std::cout << "Treated Patient: " << treated.name << ", Priority: " << treated.priority << "\n" << endl;

        Visualize();
        return treated;
        
        // Display and log the patient treated and their priority
        
        // Call visualize to display and log the entire queue
        
        // Return the dequeued patient
    }

    Patient Peek() const 
    {
        // Return the patient at the root or throw exception if the heap is empty
        if (heap.empty())
            throw out_of_range("Error: The Triage is Empty");
        return heap.top();
    }
	
	bool IsEmpty() const 
    {
		return heap.empty();
	}

    void Visualize() const 
    {
        priority_queue<Patient> tempHeap = heap;
        std::ostringstream oss;
        oss << "Current Triage Queue: ";
        while (!tempHeap.empty()) 
        {
            oss << tempHeap.top().name << " (" << tempHeap.top().priority << ") ";
            tempHeap.pop();
        }
        Print(oss.str());
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
    ofstream logFile("triage_log.txt");
    if (!logFile.is_open())
    {
        cerr << "Error: File could not be opened" << endl;
        return 1;
    }

    TriageQueue triage;
    triage.SetLogStream(&logFile);
    triage.LoadFromFile("patients.txt");
    
	while (!triage.IsEmpty()) 
    {
		std::cout << "Next Patient: " << triage.Peek().name << endl;
        logFile << "Next Patient: " << triage.Peek().name << endl;
		triage.Dequeue();
	}

    logFile.close();
    return 0;
}
