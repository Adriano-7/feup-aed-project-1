#include "Student.h"
#include <string>


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

bool Student::operator<(const Student student) {
    return name < student.name;
}

bool Student::operator==(const Student &student) {
    return this->id == student.getId();
}

void Student::addUcClass(UcClass ucClass) {
    classes.push_back(ucClass);
}