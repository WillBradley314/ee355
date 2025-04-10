
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include "person.h"
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

Network::Network(){
    head = NULL;
    tail = NULL;
    temp = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    this->loadDB(fileName);
}

Network::~Network(){
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}



Person* Network::search(string fname, string lname){
    // New == for Person, only based on fname and lname
    temp = head;
    // if found, returns a pointer to it, else returns NULL
    while (temp != NULL) {
        if (temp->f_name == fname && temp->l_name == lname) {
            return temp;
            break;
        }
        temp = temp->next;
    }
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Person with fname and lname and and using search(Person*), 2nd using fname and lname directly. 
    return NULL;
}




void Network::loadDB(string filename){
    // TODO: Complete this method
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Unable to open " << filename << "." << endl;
    }
    else {
        while (head != NULL) {
            temp = head;
            head = head->next;
            delete temp;
        }
        head = NULL;
        tail = head;
        count = 0;
        string readString, f_name, l_name, dateString, tempString, type;
        int i;


        while (std::getline(fin,f_name)) {
            Person* currNode = new Person("Default", "Default", "1/1/1111", "Default", "Default");
            
            currNode->f_name = f_name;
            std::getline(fin, currNode->l_name);
            
            std::getline(fin,dateString);
            currNode->birthdate = new Date(dateString);


            i = 1;
            tempString = "";
            type = "";
            std::getline(fin, readString);
            while (i < readString.size() && readString[i] != ')') {
                type += readString[i];
                i++;
            }
            i++;
            while (i < readString.size()) {
                if (readString[i] != ' ') {
                    tempString += readString[i];
                }
                i++;
            }
            currNode->email = new Email(type, tempString);

            i = 1;
            type = "";
            tempString = "";
            std::getline(fin, readString);
            while (i < readString.size() && readString[i] != ')') {
                type += readString[i];
                i++;
            }
            i++;
            while (i < readString.size()) {
                if (isdigit(readString[i])) {
                    tempString += readString[i];
                }
                i++;
            }
            currNode->phone = new Phone(type, tempString);

            push_front(currNode);
            std::getline(fin, readString); // skips dashes;
        }
        fin.close();
    }

}

void Network::saveDB(string filename){
    // TODO: Complete this method
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Unable to open " << filename << "." << endl;
    }
    else {
        temp = head;
        while (temp != NULL) {
            fout << temp->f_name << endl;
            fout << temp->l_name << endl;
            fout << temp->birthdate->get_dateString() << endl;
            fout << temp->email->get_contact() << endl;
            fout << temp->phone->get_contact() << endl;
            fout << "--------------------" << endl;
            temp = temp->next;
        }
        fout.close();
    }

}


void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Personattributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}



void Network::push_front(Person* newEntry){
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    // Adds a new Person (newEntry) to the back of LL
    // TODO: Complete this method
    newEntry->next = NULL;
    newEntry->prev = tail;

    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;
    
    tail = newEntry;
    count++;
}


bool Network::remove(string fname, string lname){
    // TODO: Complete this method
    Person* rm = search(fname, lname);
    if (rm == NULL) {
        return false;
    }
    if (rm == head) {
        head = rm->next;
        head->prev = NULL;
    }
    else if (rm == tail) {
        tail = rm->prev;
        tail->next = NULL;
    }
    else {
        rm->prev->next = rm->next;
        rm->next->prev = rm->prev;
    }
    count--;
    delete rm;
    return true;
}


void listFiles() {
    cout << "Networks:" << endl;
    for (const auto& file: fs::directory_iterator(".")) {
        string name = file.path().filename().string();
        vector<string> lines;
        if (name.size() > 5 && name.substr(name.size()-4) == ".txt") {
            string line;
            int nDash(0);
            ifstream fin(name);
            if (fin.is_open()) {
                while(std::getline(fin, line)) {
                    lines.push_back(line);
                    if(line == "--------------------") {
                        nDash++;
                    }
                }
                if (lines.size()/6 == nDash  && nDash) {
                    cout << name << endl;
                }
                fin.close(); 
            }
        }

    }

}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name  \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;
            saveDB(fileName);
            // Save the network database into the file with the given name,
            // with each person saved in the format the save as printing out the person info,
            // and people are delimited similar to "networkDB.txt" format
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have "networkDB.txt" format
            // print format: one filename one line.
            // This step just shows all the available .txt file to load.
            listFiles();
            cout << "Enter the name of the load file: "; 
            cin >> fileName;
            // If file with name FILENAME does not exist:
            while (!fs::exists(fileName)) { 
                cout << "File " << fileName << " does not exist!" << endl;
                cout << "Enter the correct name of the load file: "; 
                cin >> fileName;
            }

            loadDB(fileName);

            // If file is loaded successfully, also print the count of people in it: 
            cout << "Network loaded from " << fileName << " with " << count << " people \n";
            printDB();
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Person ONLY if it does not exists!
            Person* newPerson = new Person;
            remove(newPerson->f_name, newPerson->l_name);
            push_front(newPerson);
            cout << "Adding a new person \n";
        }
        else if (opt == 4){
            // TODO: Complete me!
            cout << "Removing a person \n";
            cout << "First name: " << endl;
            getline(cin, fname);
            cout << "Last name: " << endl;
            getline(cin, lname);
            if (remove(fname, lname)) {
                cout << "Remove Successful! \n";
            }
            else {
                cout << "Person not found! \n";
            }

        }
        else if (opt==5){
            // TODO: Complete me!
            // print the people with the given last name
            // if not found: cout << "Person not found! \n";
            cout << "Print people with last name \n";
            cout << "Last name: ";
        }
        
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}

