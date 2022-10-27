#ifndef TRABALHO_TEST_H
#define TRABALHO_TEST_H

#include "ScheduleManager.h"

class Test {
    public:
        Test();
        void testSortingSchedules();
        void printSchedules(ScheduleManager manager) const;
        void printStudents(ScheduleManager manager) const;
};


#endif //TRABALHO_TEST_H
