#include <iostream>

using namespace std;

struct CLLNode {
    int data;
    CLLNode* next;
};


class CircularlyLinkedList {
    CLLNode* tail; 
    CLLNode* temp1;
    CLLNode* temp2;

    public:

    CircularlyLinkedList() {
        tail = new CLLNode;
        tail->next = tail;
    }

    ~CircularlyLinkedList() {
        while (tail->next != tail) {
            temp1 = tail->next;
            temp2 = temp1->next;
            tail->next = temp2;
            delete temp1;
        }
        delete tail;
    }


    void insert(int val) {
        CLLNode* INS = new CLLNode;
        INS->data = val;
        INS->next = tail->next;
        tail->next = INS;
        cout << "Added " << val << " to front of list." << endl;
    }

    void remove(int val) {
        temp1 = tail;
        temp2 = tail->next;
        bool found = false;
        while(temp2!= tail && !found) {
            if (temp2->data == val) {
                found = true;
                temp1->next = temp2->next;
                delete temp2;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        if (found) {
            cout << "Removed " << val << "." << endl;
        }
        else {
            cout << val << " not in list, could not remove." << endl;
        }
    }

    void search(int val) {
        temp1 = tail->next;
        bool found = false;
        int i = 0;
        while(temp1!= tail && !found) {
            if (temp1->data == val) {
                found = true;

            }
            else {
                temp1 = temp1->next;
                i++;
            }
        }
        if (found) {
            cout << "Found " << val << " at element " << i << "." << endl;
        }
        else {
            cout << val << " not in list, could not find." << endl;
        }
    }

    void print() {
        temp1 = tail->next;
        cout << "CLL: ";
        while(temp1!= tail) {
            cout << temp1->data << " ";
            temp1 = temp1->next;
        }
        cout << endl;
    }

};



int main() {
    
    CircularlyLinkedList* CLL = new CircularlyLinkedList;

    CLL->insert(5);
    CLL->print();
    CLL->insert(10);
    CLL->print();
    CLL->insert(15);
    CLL->print();
    CLL->search(10);
    CLL->print();
    CLL->remove(10);
    CLL->print();
    CLL->search(10);
    CLL->print();
    CLL->remove(10);
    CLL->print();

    delete CLL;




    return 0;
}