
#ifndef TRABALHO_CLASSSCHEDULE_H
#define TRABALHO_CLASSSCHEDULE_H

#include "Slot.h"
#include "UcClass.h"

class ClassSchedule {
    public:
        ClassSchedule(UcClass ucClass);
        UcClass getUcClass() const;
        void addSlot(Slot slot);
        const vector<Slot> &getSlots() const;

private:
        UcClass ucClass;
        vector<Slot> slots = vector<Slot>();
};

#endif //TRABALHO_CLASSSCHEDULE_H
