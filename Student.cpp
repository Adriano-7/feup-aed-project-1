#include "Student.h"
#include <string>
#include <iostream>


using namespace std;

Student::Student(string id, string name) {
    this->id = id;
    this->name = name;
    this->classes = vector<UcClass>();
}

void Student::print() {
    cout << "Student: " << name << " (" << id << ")" << endl;
    cout << "Classes: " << endl;
    for (int i = 0; i < classes.size(); i++) {
        cout << classes[i].getUcId() << " " << classes[i].getClassId() << endl;
    }
}

void Student::addClass(UcClass newClass) {
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
