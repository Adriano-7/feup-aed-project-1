#include "ClassSchedule.h"
#include <iostream>

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

void ClassSchedule::print() const {
    cout << ucClass.getUcId() << " " << ucClass.getClassId() << " | Num Students: " << ucClass.getNumStudents()<< endl;
    for (const auto &slot : slots) {
        cout << slot.getWeekday() << " " << slot.getBeginTime() << " " << slot.getEndTime() << " " << slot.getType() << endl;
    }
}

void ClassSchedule::addSlot(Slot slot) {
    slots.push_back(slot);
}
void ClassSchedule::incrementNumStudents(){
    this->ucClass.setNumStudents(this->ucClass.getNumStudents() + 1);
}

UcClass ClassSchedule::getUcClass() const {
    return ucClass;
}

const vector<Slot> &ClassSchedule::getSlots() const {
    return slots;
}

bool ClassSchedule::sameUC(ClassSchedule other) const {
    return ucClass.sameUC(other.getUcClass());
}

bool ClassSchedule::operator < (const ClassSchedule &other) const {
    return this->ucClass < other.getUcClass();
}

bool ClassSchedule::operator == (const ClassSchedule &other) const {
    return this->ucClass == other.getUcClass();
}