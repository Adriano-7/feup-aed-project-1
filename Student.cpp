#include "Student.h"
#include <string>
#include <iostream>


using namespace std;

Student::Student(string id, string name, vector <UcClass> classes){
    this->id = id;
    this->name = name;
    this->classes = classes;
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

bool Student::operator==(const Student &other) {
    return this->id == other.getId();
}

bool Student::operator<(const Student &other) {
    return this->id < other.getId();
}

bool Student::operator>(const Student &other) {
    return this->id > other.getId();
}

void Student::addUcClass(UcClass ucClass) {
    classes.push_back(ucClass);
}

void Student::printStudent() {
    cout << "Student: " << name << " (" << id << ")" << endl;
    cout << "Classes: " << endl;
    for (int i = 0; i < classes.size(); i++) {
        cout << classes[i].getUcId() << " " << classes[i].getClassId() << endl;
    }
}