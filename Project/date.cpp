#include "date.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Date::Date(string date) {
    int i = 0;
    string m = "";
    string d = "";
    string y = "";

    while(date[i] != '/') {
        if (i != 0 || date[i] != '0') {
            m += date[i];
        }
        i++;
    }
    i++;
    while(date[i] != '/') {
        if (date[i] != '0' || date[i+1] == '/') {
            d += date[i];
        }
        i++;

    }
    i++;
    while(date[i] != '\0') {
        y += date[i];
        i++;
    }

    month = stoi(m);
    day = stoi(d);
    year = stoi(y);

}

void Date::print_date(string format) {

    if (format == "Month D, YYYY") {
        vector<string> months = {"January", "February", "March", "April", "May", 
        "June", "July", "August", "September", "October", "November", "December"};

        cout << months[month-1] << " " << day << ", " << year << endl;
    }
}

