
#ifndef TRABALHO_TEST_H
#define TRABALHO_TEST_H

#include "ScheduleManager.h"

class Test{
    public:
        Test(ScheduleManager manager);
        void testSortingSchedules() const;
        void printSchedules() const;
        void printStudents() const;
        void testScheduleCollisions(ScheduleManager manager) const;
        int testBSearchSchedules(UcClass desiredUcCLass) const;
        bool testClassesCollide(UcClass c1, UcClass c2);
        bool testStudentClassCollides(Student student, UcClass newClass);
        void testScheduleCollisions();

    private:
        vector<ClassSchedule> schedulesTest;
        ScheduleManager manager;
};

#endif //TRABALHO_TEST_H
