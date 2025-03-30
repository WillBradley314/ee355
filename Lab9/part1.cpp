#include <iostream>
#include <fstream> 
#include <stdexcept>
#include <string>
using namespace std;

// Define the structure for a node in the linked list
struct Node {
    int data;
    Node* next;
};

// LinkedList class encapsulates the head pointer and various operations
class LinkedList {
private:
    Node* head;
    Node* temp1;
    Node* temp2;
public:
    // Constructor initializes an empty list
    LinkedList() {
        head = new Node;
        head->next = nullptr;
        temp1 = head;
        temp2 = head;
        
    }

    // Destructor to free allocated memory
    ~LinkedList() {
        temp1 = head;
        while (temp1 != nullptr) {
            temp2 = temp1->next;
            delete temp1;
            temp1 = temp2;
        }
        
        
    }

    // Function to add an element at the beginning of the list
    void addFirst(int data) {
        Node* First = new Node;
        First->data = data;
        First->next = head->next;
        head->next = First;
    }

    // Function to append an element at the end of the list
    void append(int data) {
        Node* Last = new Node;
        Last->data = data;
        temp1 = head;
        while(temp1->next != NULL) {
            temp1 = temp1->next;
        }
        temp1->next = Last;
        Last->next = NULL;
    }

    // Function to insert an element at a specific position (0-indexed)
    void insert(int data, int pos) {
        Node* Ins = new Node;
        Ins->data = data;
        temp1 = head;
        temp2 = head->next;
        int i = 0;
        while (i < pos) {
            if (temp2->next != NULL) {
                temp1 = temp1->next;
                temp2 = temp2->next;
                i++;
            }
            else {
                temp1 = temp1->next;
                temp2 = temp2->next;
                cout << "Position out of bounds. Inserting at the end." << endl;
                break;
            }
        }
        temp1->next = Ins;
        Ins->next = temp2; 
    }

    // Function to delete the first occurrence of a node with the given value
    void deleteNode(int data) {
        temp1 = head;
        temp2 = head->next;
        if (temp2 == NULL) {
            cout << "List is empty." << endl;
        }
        else {
            while (temp2->data != data) {
                if (temp2->next != NULL) {
                    temp1 = temp1->next;
                    temp2 = temp2->next;
                }
                else {
                    cout << "Value " << data << " not found in the list." << endl;
                    return;
                }
            }
            temp1->next = temp2->next;
            delete temp2;
        }
    }

    // Function to search for an element in the list.
    // Returns a pointer to the node if found, otherwise returns nullptr.
    Node* search(int data) {
        if (head->next == NULL) {
            temp1 = nullptr;
        }
        else {
            temp1 = head->next;
            while (temp1->data != data) {
                if (temp1->next != NULL) {
                    temp1 = temp1->next;
                }
                else {
                    return nullptr;
                }
            }
        }
        return temp1;
    }

    // Function to display the linked list
    void display() {
        Node* current = head->next;
        cout << "Linked List: ";
        while (current != nullptr) {
            // Uncomment the line below to display the data
            // Here we assume the data have one element of type int and one element of pointer type
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }

        // Function to remove and return the first element of the list
    int pop() {
        if (head->next == nullptr) {
            throw runtime_error("List is empty. Cannot pop.");
        }
        temp1 = head->next;
        temp2 = temp1->next;
        int data = temp1->data;
        
        head->next = temp2;
        delete temp1;

        return data;
    }
};

int main(){

    // Open the input file "input.txt"
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Error opening input.txt" << "\n";
        return 1;
    }

    // Redirect cin to use the file stream, but keep cout as standard output.
    cin.rdbuf(infile.rdbuf());

    int T;
    cin >> T;
    string command;
    LinkedList list;
    
    // Process T commands from input
    for (int i = 0; i < T; i++){
        cin >> command;
        if (command == "addFirst") {
            int x;
            cin >> x;
            list.addFirst(x);
        } else if (command == "append") {
            int x;
            cin >> x;
            list.append(x);
        } else if (command == "insert") {
            int x, pos;
            cin >> x >> pos;
            list.insert(x, pos);
        } else if (command == "delete") {
            int x;
            cin >> x;
            list.deleteNode(x);
        } else if (command == "pop") {
            try {
                int popped = list.pop();
                cout << "Popped: " << popped << "\n";
            } catch (const runtime_error &e) {
                cout << e.what() << "\n";
            }
        } else if (command == "search") {
            int x;
            cin >> x;
            Node* found = list.search(x);
            cout << (found ? "Found" : "Not Found") << "\n";
        } else if (command == "display") {
            list.display();
        }
    }
    return 0;
}