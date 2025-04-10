
#include "contact.h"
#include <iostream>
// Add needed libraries! 

using namespace std;

Email::Email(string type, string email_addr){
    this->type = type;
    this->email_addr = email_addr;
}


void Email::set_contact(){
    // Do not change the prompts!
    cout << "Enter the type of email address: ";
    cin >> type;
    cout << "Enter email address: ";
    cin >> email_addr;
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "(" + type + ") " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << "Email " << get_contact() << endl;
}


Phone::Phone(string type, string num){
    // It is possible that num includes "-" or not, manage it!
    // Complete this method!
    // Note: We don't want to use C++11! stol is not valid!

    this->type = type;
    
    for (int i = 0; i < num.length(); i++) {
        if ((i == 3 && num[3] != '-') || (i == 7 && num[7] != '-')) {
            phone_num += '-';
        }
        phone_num += num[i];
    }
}


void Phone::set_contact(){
    // Complete this method
    // Use the same prompts as given!
    string num;
	cout <<"Enter the type of phone number: ";
    cin >> type;
	cout << "Enter the phone number: ";
    cin >> num;
    for (int i = 0; i < num.length(); i++) {
        if ((i == 3 && num[3] != '-') || (i == 7 && num[7] != '-')) {
            phone_num += '-';
        }
        phone_num += num[i];
    }
}


string Phone::get_contact(string style){
    // Complete this method, get hint from Email 
    if (style=="full")
	    return "(" + type + ") " + phone_num;
    else 
        return phone_num;
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << "Phone " << get_contact() << endl;
}

