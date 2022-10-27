#include <iostream>
#include "Test.h"

using namespace std;

Test::Test() {}


void Test::printSchedules(ScheduleManager manager) const {
    cout << "-------------- PRINTING SCHEDULES --------------" << endl;
    for (const auto &schedule : manager.getSchedules()) {
        schedule.print();
        cout << endl;
    }
}

void Test::printStudents(ScheduleManager manager) const {
    cout << "-------------- PRINTING STUDENTS --------------" << endl;
    for(Student student : manager.getStudents()) {
        student.print();
        cout << endl;
    }
}
