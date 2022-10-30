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

void Student::printClasses() const {
    cout << "Classes: ";
    int i = 0;
    while(i < classes.size()-1){
        cout << classes[i].getUcId() << " " << classes[i].getClassId() << "  |  ";
        i++;
    }
    cout << classes[i].getUcId() << " " << classes[i].getClassId() << endl;
}


void Student::print() const {
    cout << "Student: " << name << " (" << id << ")" << endl;
    printClasses();
}