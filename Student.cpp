#include "Student.h"
#include <string>


using namespace std;

Student::Student(string id, string name, Schedule schedule, double d) {
    this->id = id;
    this->name = name;
    this->schedule = schedule;
}

string Student::getId() const {
    return id;
}
string Student::getName() const {
    return name;
}
Schedule Student::getSchedule() const {
    return schedule;
}
void Student::setId(string id) {
    this->id = id;
}
void Student::setName(string name) {
    this->name = name;
}
void Student::setSchedule(Schedule schedule) {
    this->schedule = schedule;
}

bool Student::operator<(const Student student) {
    return name < student.name;
}

bool Student::operator==(const Student &student) {
    return this->id == student.getId();
}
