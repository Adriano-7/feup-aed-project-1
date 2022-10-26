#include "ClassSchedule.h"

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

const vector<Slot> &ClassSchedule::getSlots() const {
    return slots;
}
