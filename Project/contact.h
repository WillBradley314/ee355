
#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
// You may need to add other libraries here!
using namespace std;


class Contact {
    // private or protected? Look at your children!
protected:	
	string type;
public:
	virtual void print() = 0;
    virtual string get_contact(string style="full") = 0;
	virtual void set_contact() = 0;
};


class Email: public Contact{
private:
    string email_addr;
public:
    Email(string type, string email_addr);
    void print();
    string get_contact(string style = "full");
    void set_contact();

    // Complete me!
};


class Phone: public Contact{
private:
    // modify dataType! Can int store 10 digit phone-number? 
	string phone_num; 
public:
    Phone(string type, string phone_number);
    void print();
    string get_contact(string style = "full");
    void set_contact();
    // Complete me!
};

#endif