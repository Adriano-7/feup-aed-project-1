#include "Class.h"


using namespace std;

Class::Class(string id, Schedule schedule, vector<Student> students) {
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

vector<Student> Class::getStudents() const {
    return students;
}

void Class::setId(string id) {
    this->id = id;
}

void Class::setSchedule(Schedule schedule) {
    this->schedule = schedule;
}

void Class::setStudents(vector<Student> students) {
    this->students = students;
}

void Class::addStudent(Student student) {
    students.push_back(student);
}

void Class::removeStudent(Student student) {
    students.erase(find(students.begin(),students.end(),student));
}


