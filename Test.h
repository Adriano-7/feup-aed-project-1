#ifndef TRABALHO_TEST_H
#define TRABALHO_TEST_H

#include "ScheduleManager.h"

class Test : public ScheduleManager {
    public:
        Test();
        void testSortingSchedules() const;
        void printSchedules(ScheduleManager manager) const;
        void printStudents(ScheduleManager manager) const;
        int testBSearchSchedules(UcClass desiredUcCLass) const;
        bool testClassesCollide(UcClass c1, UcClass c2);
        bool testStudentClassCollides(Student student, UcClass newClass);
        void testScheduleCollisions();

    private:
        vector<ClassSchedule> schedulesTest;
};

#endif //TRABALHO_TEST_H
