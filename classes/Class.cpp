#include "Class.h"
#include <string>
#include "Schedule.h"
#include <set>

using namespace std;

Class::Class(string id, Schedule schedule, set<Student> students) {
    this->id = id;
    this->schedule = schedule;
    this->students = students;
}

string Class::getId() const {
    return id;
}

Schedule Class::getSchedule() const {
    return schedule;
}

set<Student> Class::getStudents() const {
    return students;
}

void Class::setId(string id) {
    this->id = id;
}

void Class::setSchedule(Schedule schedule) {
    this->schedule = schedule;
}

void Class::setStudents(set<Student> students) {
    this->students = students;
}

void Class::addStudent(Student student) {
    students.insert(student);
}

void Class::removeStudent(Student student) {
    students.erase(student);
}
