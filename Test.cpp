#include <iostream>
#include "Test.h"

using namespace std;

Test::Test() {}


void Test::printSchedules(ScheduleManager manager) const {
    cout << "-------------- PRINTING SCHEDULES --------------" << endl;
    for (const auto &schedule : manager.getSchedules()) {
        cout << schedule.getUcClass().getUcId() << " " << schedule.getUcClass().getClassId() << endl;
        for (const auto &slot : schedule.getSlots()) {
            cout << slot.getWeekday() << " " << slot.getBeginTime() << " " << slot.getEndTime() << " " << slot.getType() << endl;
        }
        cout << endl;
    }
}

void Test::printStudents(ScheduleManager manager) const {
    cout << "-------------- PRINTING STUDENTS --------------" << endl;
    for(Student student : manager.getStudents()) {
        student.printStudent();
        cout << endl;
    }
}
