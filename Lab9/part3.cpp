#include <iostream>
#include <fstream>
using namespace std;

// Define the structure for a node in the circular linked list
struct Node {
};

class CircularQueue {
private:
   

public:
    // Constructor initializes an empty queue
    CircularQueue() {
        
    }

    // Destructor to free allocated memory
    ~CircularQueue() {
        
    }

    // Function to check if the queue is empty
    bool isEmpty() {
    }

    // Function to check if the queue is full
    bool isFull() {
    }

    // Function to add an element to the end of the queue (enqueue)
    void enqueue(int data) {
        // If the queue is full
        // cout << "Queue is full. Cannot enqueue " << data << "." << endl;
        
        // Output the information about the enqueued element
        // cout << "Enqueued: " << data << " (size: " << count << ")" << endl;
    }

    // Function to remove an element from the front of the queue (dequeue)
    int dequeue() {
        // If the queue is empty
        // cout << "Queue is empty. Cannot dequeue." << endl;
        
        // Output the information about the dequeued element
        cout << "Dequeued: " << value << " (size: " << count << ")" << endl;
    }

    // Function to get the front element of the queue (peek)
    int peek() {
        // If the queue is empty
        // cout << "Queue is empty." << endl;
    }

    // Function to display the queue elements
    void display() {
    }
};

int main() {
    // Open the input file "input_part3.txt"
    ifstream infile("input_part3.txt");
    if (!infile) {
        cerr << "Error opening input_part3.txt" << "\n";
        return 1;
    }
    
    // Redirect standard input to read from the file
    cin.rdbuf(infile.rdbuf());

    int T;
    cin >> T;
    string command;
    CircularQueue cq;
    
    // Process T commands from input_part3.txt
    for (int i = 0; i < T; i++){
        cin >> command;
        if (command == "enqueue") {
            int x;
            cin >> x;
            cq.enqueue(x);
        } else if (command == "dequeue") {
            cq.dequeue();
        } else if (command == "peek") {
            int front = cq.peek();
            if(front != -1)
                cout << "Front element: " << front << "\n";
        } else if (command == "display") {
            cq.display();
        } else {
            cout << "Unknown command: " << command << "\n";
        }
    }
    
    return 0;
}