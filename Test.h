
#ifndef TRABALHO_TEST_H
#define TRABALHO_TEST_H

#include "ScheduleManager.h"

class Test {
    public:
        void testSortingSchedules() const;
        void printSchedules(ScheduleManager manager) const;
        void printStudents(ScheduleManager manager) const;
        void testScheduleCollisions(ScheduleManager manager) const;
};

#endif //TRABALHO_TEST_H
