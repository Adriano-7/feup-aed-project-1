#include <iostream>
#include <algorithm>
#include "Test.h"

using namespace std;

Test::Test(){
    schedulesTest = vector<ClassSchedule>();
}

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


int Test::testBSearchSchedules(UcClass desiredUcCLass) const {
    int left = 0;
    int right = schedulesTest.size() - 1;
    int middle = (left + right) / 2;

    while(left <= right){
        if(schedulesTest[middle].getUcClass() == desiredUcCLass){
            return middle;
        }
        else if(schedulesTest[middle].getUcClass() < desiredUcCLass){
            left = middle + 1;
        }
        else{
            right = middle - 1;
        }
        middle = (left + right) / 2;
    }
    return -1;
}

bool Test::testClassesCollide(UcClass c1, UcClass c2) {
    if(c1.sameUC(c2)) return false;
    ClassSchedule cs1 = schedulesTest[testBSearchSchedules(c1)];
    ClassSchedule cs2 = schedulesTest[testBSearchSchedules(c2)];
    for(Slot slot1 : cs1.getSlots()){
        for(Slot slot2 : cs2.getSlots()){
            if(slot1.collides(slot2)) return true;
        }
    }
    return false;
}

bool Test::testStudentClassCollides(Student student, UcClass newClass){
    vector<UcClass> studentClasses = student.getClasses();
    for(UcClass ucClass : studentClasses){
        if(testClassesCollide(ucClass, newClass)) return true;
    }
    return false;
}


void Test::testScheduleCollisions(){
    /*
    this->schedulesTest = vector<ClassSchedule>();

    // Test if two UcClasses with different UCs collide (they must not collide)
    ClassSchedule cs1 = ClassSchedule("L.EIC021", "3LEIC04");
    ClassSchedule cs2 = ClassSchedule("L.EIC022","3LEIC02");
    cs1.addSlot(Slot("Tuesday", 8.5, 10.5, "TP"));
    cs1.addSlot(Slot("Friday", 9.5, 10.5, "T"));
    cs1.addSlot(Slot("Wednesday", 9.5, 10.5, "T"));
    cs2.addSlot(Slot("Monday", 10.5, 11.5, "TP"));
    cs2.addSlot(Slot("Wednesday", 8.0, 9.5, "T"));


    ClassSchedule cs3 = ClassSchedule("L.EIC023", "3LEIC07");
    ClassSchedule cs4 = ClassSchedule("L.EIC023", "3LEIC08");





    cs3.addSlot(Slot("Friday", 10.5, 12.5, "PL"));
    cs3.addSlot(Slot("Monday", 8.5, 10.5, "T"));

    cs4.addSlot(Slot("Friday", 10.5, 12.5, "PL"));
    cs4.addSlot(Slot("Monday", 8.5, 10.5, "T"));

    schedulesTest.push_back(cs1);
    schedulesTest.push_back(cs2);
    schedulesTest.push_back(cs3);

    Student testStudent("202031607", "Adriano");
    testStudent.addClass(UcClass("L.EIC002", "1LEIC02"));
    testStudent.addClass(UcClass("L.EIC001", "1LEIC01"));
    testStudent.addClass(UcClass("L.EIC023", "3LEIC13"));

     */
}