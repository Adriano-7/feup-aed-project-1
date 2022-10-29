#include "ClassSchedule.h"
#include <iostream>
#include <algorithm>

using namespace std;

ClassSchedule::ClassSchedule() {
    this->ucClass = UcClass();
    this->slots = vector<Slot>();
}

ClassSchedule::ClassSchedule(UcClass ucClass) {
    this->ucClass = ucClass;
    this->slots = vector<Slot>();
}

ClassSchedule::ClassSchedule(string ucId, string classId) {
    UcClass ucClass = UcClass(ucId, classId);
    this->ucClass = ucClass;
    this->slots = vector<Slot>();
}


void ClassSchedule::addSlot(Slot slot) {
    slots.push_back(slot);
}

UcClass ClassSchedule::getUcClass() const {
    return ucClass;
}

void ClassSchedule::addStudent(Student student) {
    students.insert(student);
}

int ClassSchedule::getNumStudents() const {
    return students.size();
}

const vector<Slot> &ClassSchedule::getSlots() const {
    return slots;
}

bool ClassSchedule::sameUC(ClassSchedule other) const {
    return ucClass.sameUcId(other.getUcClass());
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

void ClassSchedule::printStudents() const{
    vector<Student>* studentsVector = new vector<Student>(students.begin(), students.end());
    sort(studentsVector->begin(), studentsVector->end(), [](const Student &a, const Student &b) {
        return a.getName() < b.getName();
    });
    cout << ">> Number of students: " << students.size() << endl;
    cout << ">> Students:" << endl;
    for(Student student: *studentsVector){
        cout << "   " << student.getName() << " - " << student.getId() << endl;
    }
    delete studentsVector;
}

void ClassSchedule::print() const {
    printHeader();
    printSlots();
    printStudents();
    cout << endl;
}