
#ifndef TRABALHO_TEST_H
#define TRABALHO_TEST_H

#include "ScheduleManager.h"

/**
 * @brief Class to test the methods in our project.
 */

class Test{
    public:
        /** Constructor
         * @param manager, ScheduleManager compound of a set of students, a vector of schedules and a queue of requests
         */
        Test(ScheduleManager manager);
        /** Method to test the sort() in ScheduleManager
         */
        void testSortingSchedules() const;
        /** Method to print the schedules in the terminal
         */
        void printSchedules() const;
        /** Method to print the students in the terminal
         */
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
