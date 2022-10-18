
#ifndef TRABALHO_CLASSSCHEDULE_H
#define TRABALHO_CLASSSCHEDULE_H

#include "Slot.h"
#include "UcClass.h"

class ClassSchedule {
    public:
        ClassSchedule(UcClass ucClass);
        void addSlot(Slot slot);

    private:
        UcClass ucClass;
        vector<Slot> slots = vector<Slot>();
};

#endif //TRABALHO_CLASSSCHEDULE_H
