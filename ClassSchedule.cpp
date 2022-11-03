#include "ClassSchedule.h"
#include <iostream>
#include <algorithm>

using namespace std;


ClassSchedule::ClassSchedule() {
    this->ucClass = UcClass();
    this->slots = vector<Slot>();
}

ClassSchedule::ClassSchedule(const UcClass &ucClass) {
    this->ucClass = ucClass;
    this->slots = vector<Slot>();
}

ClassSchedule::ClassSchedule(const string &ucId, const string &classId) {
    this->ucClass = UcClass(ucId, classId);
    this->slots = vector<Slot>();
}


void ClassSchedule::addSlot(const Slot &slot) {
    slots.push_back(slot);
}

void ClassSchedule::addStudent(const Student &student) {
    students.insert(student);
}

void ClassSchedule::removeStudent(const Student &student) {
    students.erase(student);
}

UcClass ClassSchedule::getUcClass() const {
    return ucClass;
}

int ClassSchedule::getNumStudents() const {
    return students.size();
}

const vector<Slot> &ClassSchedule::getSlots() const {
    return slots;
}

set<Student> ClassSchedule::getStudents() const {
    return students;
}

bool ClassSchedule::sameUC(const ClassSchedule &other) const {
    return ucClass.sameUC(other.getUcClass());
}

bool ClassSchedule::operator < (const ClassSchedule &other) const {
    return this->ucClass < other.getUcClass();
}

bool ClassSchedule::operator == (const ClassSchedule &other) const {
    return this->ucClass == other.getUcClass();
}


void ClassSchedule::printHeader() const {
    cout << ">> UC:" << ucClass.getUcId() << " " << ucClass.getClassId() << endl;
}

void ClassSchedule::printSlots() const {
    cout << ">> Slots:" << endl;
    for (const auto &slot : slots) {
        cout << "   " << slot.getWeekDay() << "   " << slot.getStartTime() << " - " << slot.getEndTime() << "   " << slot.getType() << endl;
    }
}

void ClassSchedule::printStudents(const string &sortType) const{
    auto studentsVector = new vector<Student>(students.begin(), students.end());
    if (sortType == "alphabetical") {
        sort(studentsVector->begin(), studentsVector->end(), [](const Student &a, const Student &b) { return a.getName() < b.getName(); });
    } else if (sortType == "reverse alphabetical") {
        sort(studentsVector->rbegin(), studentsVector->rend(), [](const Student &a, const Student &b) { return a.getName() < b.getName(); });
    } else if (sortType == "numerical") {
        sort(studentsVector->begin(), studentsVector->end());
    } else if (sortType == "reverse numerical") {
        sort(studentsVector->rbegin(), studentsVector->rend());
    } else {
        cout << "Invalid sortType" << endl;
        return;
    }
    cout << ">> Number of students: " << students.size() << endl;
    cout << ">> Students:" << endl;
    for(const Student &student: *studentsVector){
        cout << "   "; student.printHeader();
    }
    delete studentsVector;
}


void ClassSchedule::print() const {
    printHeader();
    printSlots();
    printStudents();
    cout << endl;
}