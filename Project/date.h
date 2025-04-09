#ifndef DATE_H
#define DATE_H

#include <string>

using namespace std;

class Date {
    int month, day, year;
public:
    Date(string date);
    void print_date(string format);
};


#endif