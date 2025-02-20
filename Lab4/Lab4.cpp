#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;



class Person {
    protected:
        string name;
        int age;  
    public:    
        Person(int age, string name) : age(age), name(name) {}
        virtual void displayPersonInfo(ofstream& fout) {}
        virtual void displayInfo(ofstream& fout) = 0;
        virtual void introduce(ofstream& fout) {}
};

class Student : public Person {
    protected:
        string ID;
        float GPA;
    public:
        Student(string name, int age, string ID, float GPA) : Person(age, name), ID(ID), GPA(GPA) {}
        void displayPersonInfo(ofstream& fout) {
            fout << "Public Inheritance: Person: " << name << ", Age: " << age << endl;
        }
        void displayInfo(ofstream& fout) {
            fout << "Student: " << name << ", Age: " << age << ", ID: " << ID << ", GPA: " << GPA << endl;
        }
        void introduce(ofstream& fout) override {
            fout << "I am a student. My name is " << name << "." << endl;
        }


};

class StudentPrivate : private Person {  
    protected:
        string ID;
        float GPA;
    public:
        StudentPrivate(string name, int age, string ID, float GPA) : Person(age, name), ID(ID), GPA(GPA) {}
        void displayPersonInfo(ofstream& fout) {
            fout << "Private Inheritance: Person: " << name << ", Age: " << age << endl;
        }
        void displayInfo(ofstream& fout) {}
};

class Teacher : public Person {
    protected:
        string subject;
        int experience;
    public:
        Teacher(string name, int age, string subject, int experience) : Person(age, name), subject(subject), 
        experience(experience) {}
        void displayInfo(ofstream& fout) {
            fout << "Teacher: " << name << ", Age: " << age << ", Subject: " << subject << ", Experience: "
            << experience << " years" << endl;
        }
        void introduce(ofstream& fout) override {
            fout << "I am a teacher. My name is " << name << "." << endl;
        }
};






int main() {

    vector<Person*> people;
    vector<Person*> students;
    ifstream fin;
    int n;
    ofstream fout;

    fin.open("input.txt");
    fin >> n;
    if (!fin.is_open()) {
        cerr << "Could not open file."  << endl;
    } 
    else {
        for (int i = 0; i < n; i++) {
            string occupation, name, subject, ID;
            int age, experience;
            float GPA;

            fin >> occupation >> name >> age;

            if (occupation == "Student") {
                fin >> ID >> GPA;
                people.push_back(new Student(name, age, ID, GPA));
                // students.push_back(new StudentPrivate(name, age, ID, GPA)); for Q1, doesn't work bc private inheritance
            }
            else {
                fin >> subject >> experience;
                people.push_back(new Teacher(name, age, subject, experience));

            }
        }
        fin.close();
    }


    fout.open("output_Q1.txt");
    if (!fout.is_open()) {
        cerr << "Could not open file."  << endl;
    } 
    else {
        for (int i = 0; i < people.size(); i++) {
            people[i]->displayPersonInfo(fout);
        }
        for (int i = 0; i < students.size(); i++) {
            // students[i]->displayPersonInfo(fout); for Q1, doesn't work bc private inheritance.
        }

        fout.close();
    }


    fout.open("output_Q2.txt");
    if (!fout.is_open()) {
        cerr << "Could not open file."  << endl;
    } 
    else {
        for (int i = 0; i < people.size(); i++) {
            people[i]->displayInfo(fout);
        }
        fout.close();
    }


    fout.open("output_Q3.txt");
    if (!fout.is_open()) {
        cerr << "Could not open file."  << endl;
    } 
    else {
        for (int i = 0; i < people.size(); i++) {
            people[i]->introduce(fout);  // used vector instead of array bc TA said we could keep same data structure.
        }
        fout.close();
    }
    


    for(auto person : people) {
        delete person;
    }


    return 0;
}


