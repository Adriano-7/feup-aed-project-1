#include <iostream>
#include <algorithm>
#include "Test.h"

using namespace std;

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

void Test::testSortingSchedules() const {
    ClassSchedule   cs1 = ClassSchedule("L.EIC002", "1LEIC02"),
                    cs2 = ClassSchedule("L.EIC001","1LEIC01"),
                    cs3 = ClassSchedule("L.EIC023", "3LEIC13");
    vector<ClassSchedule> testSchedules = {cs1, cs2, cs3};
    vector<ClassSchedule> expectedSchedules1 = {cs2, cs1, cs3};
    vector<ClassSchedule> expectedSchedules2 = {cs3, cs1, cs2};
    sort(testSchedules.begin(), testSchedules.end());
    if(testSchedules == expectedSchedules1) {
        cout << "First test - Sorting Schedules Test Passed" << endl;
    } else {
        cout << "First test - Sorting Schedules Test Failed" << endl;
    }
    if(testSchedules == expectedSchedules2){
        cout << "Second test - Sorting Schedules Test Failed" << endl;
    } else {
        cout << "Second test - Sorting Schedules Test Passed" << endl;
    }
}