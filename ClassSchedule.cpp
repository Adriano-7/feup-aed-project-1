#include "ClassSchedule.h"

ClassSchedule::ClassSchedule(UcClass ucClass) {
    this->ucClass = ucClass;
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
