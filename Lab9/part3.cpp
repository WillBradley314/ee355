#include <iostream>
#include <fstream>
using namespace std;

// Define the structure for a node in the circular linked list
struct Node {
    int data;
    Node* next;
};

class CircularQueue {
private:
   Node* tail = new Node;
   Node* temp1 = new Node;
   Node* temp2 = new Node;
   int count;

public:
    // Constructor initializes an empty queue
    CircularQueue() {
        count = 0;
        tail->next = tail;
    }

    // Destructor to free allocated memory
    ~CircularQueue() {
        while (!isEmpty()) {
            temp1 = tail->next;
            int value = temp1->data;
            if (tail->next == tail) {
                delete temp1;
                tail->next = tail;
            }
            else {
                tail->next = temp1->next;
                delete temp1;
            }
            count--;        
        }
    }

    // Function to check if the queue is empty
    bool isEmpty() {
        return (count == 0);
    }

    // Function to check if the queue is full
    bool isFull() {
        return (count > 7);
    }

    // Function to add an element to the end of the queue (enqueue)
    void enqueue(int data) {
        // If the queue is full
        // cout << "Queue is full. Cannot enqueue " << data << "." << endl;
        if (isFull()) {
            cout << "Queue is full. Cannot enqueue " << data << "." << endl;
        }
        else {
            Node* enq = new Node;
            enq->data = data;
            if (isEmpty()) {
                enq->next = enq;
                tail = enq;
            }
            else {
                enq->next = tail->next;
                tail->next = enq;
                tail = enq;
            }
        

            count++;
            cout << "Enqueued: " << data << " (size: " << count << ")" << endl;
        }
        // Output the information about the enqueued element
        // cout << "Enqueued: " << data << " (size: " << count << ")" << endl;
    }

    // Function to remove an element from the front of the queue (dequeue)
    int dequeue() {
        // If the queue is empty
        // cout << "Queue is empty. Cannot dequeue." << endl;
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return -1;
        }
        else {
            temp1 = tail->next;
            int value = temp1->data;
            if (tail->next == tail) {
                delete temp1;
                tail->next = tail;
            }
            else {
                tail->next = temp1->next;
                delete temp1;
            }

            
        
            
            count--;
            cout << "Dequeued: " << value << " (size: " << count << ")" << endl;
            return value;
        }
        // Output the information about the dequeued element
    }

    // Function to get the front element of the queue (peek)
    int peek() {
        // If the queue is empty
        // cout << "Queue is empty." << endl;
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return -1;
        }
        else {
            return tail->next->data;
        }
    }

    // Function to display the queue elements
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
        }
        else {
        
            temp1 = tail->next;
            
            cout << "Circular Queue: ";
            do {
                cout << temp1->data << " -> ";
                temp1 = temp1->next;
            } while(temp1 != tail->next);
            cout << "(back to head)" << endl;
        }
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