#include <fstream>
#include <cctype>
#include "person.h"
#include "contact.h"
#include "date.h"
#include "misc.h"

Person::Person(){
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
}


Person::Person(string f_name, string l_name, string b_date, string email, string phone){
    string type, tempString;
    int i = 1;

    this->f_name = f_name;
    this->l_name = l_name;
    this->ID = nameToID(f_name, l_name);
    this->birthdate = new Date(b_date);
    
    while (email[i] != ')' && i < email.size()) {
        type += email[i];
        i++;
    }
    i++;
    while (email[i] != '\0') {
        if (email[i] != ' ') {
            tempString += email[i];
        }
        i++;
    }
    this->email = new Email(type, tempString);

    i = 1;
    tempString = "";
    type = "";

    while (phone[i] != ')' && phone[i] != '\0') {
        type += phone[i];
        i++;
    }
    i++;
    while (phone[i] != '\0') {
        if (phone[i] != ' ') {
            tempString += phone[i];
        }
        i++;
    }
    this->phone = new Phone(type, tempString);
}


Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    
    string temp;
    string type;

    cout << "First Name: ";
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    ID = nameToID(f_name, l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    cin >> type;
    cout << "Email address: ";
    cin >> temp;
    email = new Email (type, temp);

    cout << "Type of phone number: ";
    cin >> type;
    cout << "Phone number: ";
    cin >> temp;
    phone = new Phone (type, temp);
}


void Person::set_person(string filename){
    ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        cerr << "Unable to open " << filename << "." << endl;
    }
    else {
        string dateString, readString, tempString, type;
        int i = 1;
        
        std::getline(fin,f_name);
        std::getline(fin,l_name);
        ID = nameToID(f_name, l_name);

        std::getline(fin,dateString);
        birthdate = new Date(dateString);

        std::getline(fin, readString);
        while (readString[i] != ')') {
            type += readString[i];
            i++;
        }
        i++;
        while (readString[i] != '\0') {
            if (isdigit(readString[i])) {
                tempString += readString[i];
            }
            i++;
        }
        phone = new Phone(type, tempString);

        i = 1;
        tempString = "";
        type = "";

        std::getline(fin, readString);
        while (readString[i] != ')') {
            type += readString[i];
            i++;
        }
        i++;
        while (readString[i] != '\0') {
            if (readString[i] != ' ') {
                tempString += readString[i];
            }
            i++;
        }
        email = new Email(type, tempString);


        fin.close();
    }
}


bool Person::operator==(const Person& rhs){
    return (this->f_name == rhs.f_name && this->l_name == rhs.l_name 
    && this->birthdate == rhs.birthdate);
}

bool Person::operator!=(const Person& rhs){ 
    return !(this->operator==(rhs));
}

void Person::print_person(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    phone->print();
    email->print();
    for(int i = 0; i < myfriends.size(); i++) {
        cout << nameToID(myfriends[i]->f_name, myfriends[i]->l_name) << "(" 
        << myfriends[i]->f_name << " " << myfriends[i]->l_name << ")" << endl;
    }
}

bool Person::makeFriend(Person* newFriend){
    for (int i = 0; i < myfriends.size(); i++) {
        if (newFriend->operator==(*myfriends[i])) {
            return true;
        }
    }
    myfriends.push_back(newFriend);
    return false;
}

void Person::print_friends() {
    Person* temp;
    for (int i = 0; i < myfriends.size(); i++) {
        for (int j = 0; j < myfriends.size()-1; j++) {
            if(myfriends[j]->ID[0] > myfriends[j+1]->ID[0]) {
                temp = myfriends[j];
                myfriends[j] = myfriends[j+1];
                myfriends[j+1] = temp;
            }
            else if (myfriends[j]->ID[0] == myfriends[j+1]->ID[0]) {
                if (myfriends[j]->ID[1] > myfriends[j+1]->ID[1]) {
                    temp = myfriends[j];
                    myfriends[j] = myfriends[j+1];
                    myfriends[j+1] = temp;
                }
            }
        }
    }
    cout << f_name << ", " << l_name << endl << "--------------------------------" << endl;
    for (int i = 0; i < myfriends.size(); i++) {
        cout << myfriends[i]->f_name << ", " << myfriends[i]->l_name << endl;
    }
}