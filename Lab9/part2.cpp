#include <iostream>
#include <fstream>
using namespace std;

// Define the structure for a node in the doubly linked list
struct Node {
    int data;
    Node* next;
    Node* prev;
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    Node* temp1;
    Node* temp2;
public:
    // Constructor initializes an empty list
    DoublyLinkedList() {
        head = new Node;
        tail = new Node;
        head->next = tail;
        head->prev = nullptr;
        tail->prev = head;
        tail->next = nullptr;
        temp1 = head;
    }

    // Destructor to free allocated memory
    ~DoublyLinkedList() {
        temp1 = tail->prev;
        while (temp1 != head) {
            delete temp1;
            temp1 = temp1->prev;
            tail->prev = temp1;
        }
    }

    // Function to add an element at the beginning of the list
    void addFirst(int data) {
        Node* First = new Node;
        First->data = data;
        temp1 = head->next;
        head->next = First;
        First->prev = head;
        First->next = temp1;
        temp1->prev = First;
    }

    // Function to append an element at the end of the list
    void append(int data) {
        Node* Last = new Node;
        Last->data = data;
        temp1 = tail->prev;
        tail->prev = Last;
        Last->next = tail;
        Last->prev = temp1;
        temp1->next = Last;
    }

    // Function to insert an element at a specific position (0-indexed)
    void insert(int data, int pos) {
        Node* Ins = new Node;
        Ins->data = data;
        temp1 = head;
        temp2 = head->next;
        for (int i = 0; i < pos; i++) {
            if (temp2 != tail) {
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            else {
                cout << "Position out of bounds. Inserting at the end." << endl;
            }
        }
        Ins->prev = temp2->prev;
        Ins->next = temp2;
        temp1->next = Ins;
        temp2->prev = Ins;
        // If we reached the end, append at the end
    }

    // Function to delete the node at a specific index (0-indexed)
    void deleteAtIndex(int index) {
        // if the index is Invalid or the list is empty
        // cout << "Invalid index or empty list." << endl;
        
        if (head->next == tail | index < 0) {
            cout << "Invalid index or empty list." << endl;
            return;
        }

        temp1 = head;
        temp2 = head->next;

        for (int i = 0; i < index; i++) {
            if (temp2->next == tail) {
                cout << "Index out of bounds." << endl;
                break;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        temp1->next = temp2->next;
        temp1 = temp2->next;
        temp1->prev = temp2->prev;
        delete temp2;
        

        // If the index is out of bounds
        // cout << "Index out of bounds." << endl;

    }

    // Function to search for an element in the list.
    // Returns a pointer to the node if found, otherwise returns nullptr.
    Node* search(int data) {
        temp1 = head->next;
            while (temp1 != tail) {
                if (temp1->data == data) {
                    return temp1;
                }
                temp1 = temp1->next;
            }
            return nullptr;
    }

    // Function to check whether the doubly linked list is circular using two pointers.
    // The list is considered circular if there is a cycle in the next pointers.
    bool isCircularTwoPointer() {
        temp1 = head->next;
        temp2 = head->next;
        while (temp2 != nullptr && temp2->next != nullptr && temp2->next->next != nullptr) {
            temp1 = temp1->next;
            temp2 = temp2->next;
            temp2 = temp2->next;
            if (temp1 == temp2) {
                return true;
            }
        }
        return false;
    }

    // Function to display the doubly linked list
    void display() {
        Node* current = head->next;
        cout << "Doubly Linked List: ";
        while (current != tail) {
            // Uncomment the line below to display the data
            // Here we assume the data have one element of type int and one element of pointer type

             cout << current->data << " <-> ";
             current = current->next;
        }
         cout << "NULL" << endl;
    }
};

int main() {
    // Open input.txt file for reading
    std::ifstream infile("input_part2.txt");
    if (!infile) {
        std::cerr << "Error opening input.txt" << "\n";
        return 1;
    }
    
    // Redirect cin to read from input.txt
    cin.rdbuf(infile.rdbuf());

    int T;
    cin >> T;
    string command;
    DoublyLinkedList dll;
    
    // Process T commands from the input file
    for (int i = 0; i < T; i++){
        cin >> command;
        if (command == "addFirst") {
            int x;
            cin >> x;
            dll.addFirst(x);
        } else if (command == "append") {
            int x;
            cin >> x;
            dll.append(x);
        } else if (command == "insert") {
            int x, pos;
            cin >> x >> pos;
            dll.insert(x, pos);
        } else if (command == "deleteAtIndex") {
            int idx;
            cin >> idx;
            dll.deleteAtIndex(idx);
        } else if (command == "search") {
            int x;
            cin >> x;
            Node* found = dll.search(x);
            cout << (found ? "Found" : "Not Found") << "\n";
        } else if (command == "display") {
            dll.display();
        } else if (command == "isCircular") {
            cout << "Is the list circular (two-pointer check)? " 
                 << (dll.isCircularTwoPointer() ? "Yes" : "No") << "\n";
        }
    }
    return 0;
}