#include "Student.h"
#include <string>
#include <iostream>

using namespace std;

Student::Student() {
    this->id = "";
    this->name = "";
    this->classes = vector<UcClass>();
}

Student::Student(const string &id, const string &name) {
    this->id = id;
    this->name = name;
    this->classes = vector<UcClass>();
}

void Student::addClass(const UcClass &newClass) {
    classes.push_back(newClass);
}

string Student::getId() const {
    return id;
}

string Student::getName() const {
    return name;
}

vector <UcClass> Student::getClasses() const {
    return classes;
}

bool Student::operator==(const Student &other) const{
    return this->id == other.getId();
}

bool Student::operator<(const Student &other) const {
    return this->id < other.getId();
}

bool Student::operator>(const Student &other) const {
    return this->id > other.getId();
}

void Student::print() const {
    cout << "Student: " << name << " (" << id << ")" << endl;
    cout << "Classes: ";
    for (const UcClass &ucClass : classes) {
        cout << ucClass.getUcId() << " " << ucClass.getClassId() << "  |  ";
    }
    cout << endl;
}