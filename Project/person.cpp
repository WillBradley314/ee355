#include <fstream>
#include <cctype>
#include "person.h"
#include "contact.h"
#include "date.h"

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
    // TODO: complete the method!
}


Person::Person(string f_name, string l_name, string b_date, string email, string phone){
    // Complete this method!
    // phone and email strings are in full version

    string type, tempString;
    int i = 1;

    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(b_date);
    
    while (email[i] != ')' && email[i] != '\0') {
        type += email[i];
        i++;
    }
    while (email[i] != '\0') {
        if (email[i] != ' ') {
            tempString += email[i];
        }
        i++;
    }
    this->email = new Email(type, tempString); // fix separate into type and email

    i = 1;
    tempString = "";
    type = "";

    while (phone[i] != ')' && email[i] != '\0') {
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
    // complete this method!
    
    string temp;
    string type;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    // code here
    cin >> type;
    cout << "Email address: ";
    // code here
    cin >> temp;
    email = new Email (type, temp);

    cout << "Type of phone number: ";
    // code here
    cin >> type;
    cout << "Phone number: ";
    // code 
    cin >> temp;
    // code here
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
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // TODO: Complete this method!
}


bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    if (this->f_name == rhs.f_name && this->l_name == rhs.l_name && this->birthdate == rhs.birthdate) {
        return true;
    }
    else {
        return false;
    }
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Person::print_person(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    phone->print();
    email->print();
}
