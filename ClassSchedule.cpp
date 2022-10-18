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