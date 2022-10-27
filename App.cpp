//
// Created by evans24 on 27-10-2022.
//

#include "App.h"
#include "Test.h"
#include <iostream>
#include <utility>
#include <cmath>

using namespace std;

string decimalToHours(int decimal){
    double time = 10.5;
    int time_mins = (int)floor( time * 60.0 );
    int hours = time_mins / 60;
    int minutes = time_mins % 60;
    return (to_string(hours) + ":" + to_string(minutes));
}

App::App(ScheduleManager manager) {
    this->manager = manager;
    cout << "Schedule manager is online" << endl << endl;
}

int App::run() {
    manager.readFiles();
    int option;
    while (true) {
        cout << "What would you like to do next?" << endl << endl << "1 Check the schedule of a student" << endl
             << "2 Check the schedule of a Class" << endl << "3 Check the students in Class " << endl
             << "4 Check the schedule of a Subject " << endl << "5 Make a changing request" << endl
             << "8 Exit" << endl;
        cin >> option;
        if (cin.fail()) {
            throw invalid_argument("Please choose a valid number");
        }
        switch (option) {
            case 1:{
                cout << "Please insert the student's up number" << endl;
                string upNumber;
                cin >> upNumber;

                Student student = Student(upNumber, "");
                auto loc = manager.getStudents().find(student);
                if (loc == manager.getStudents().end()) {
                    cout << "Student not found" << endl;
                    return 0;
                }
                Student modStudent = *loc;
                vector<UcClass> studentClasses = modStudent.getClasses();
                vector<vector<pair<string, Slot>>> weekdays = vector<vector<pair<string, Slot>>>(5);
                vector<string> weekdaysNames = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
                cout << "The student " << modStudent.getName() << " with up number " << modStudent.getId()
                     << " is enrolled in the following classes:" << endl;
                for (UcClass classs: studentClasses) {
                    cout << classs.getUcId() << " " << classs.getClassId() << endl;
                }

                for (UcClass ucClass: studentClasses) {
                    ClassSchedule cs = manager.getSchedules()[manager.BSearchSchedules(ucClass)];
                    vector<pair<string, Slot>> slots;
                    for (Slot slot: cs.getSlots()) {
                        slots.push_back(make_pair(cs.getUcClass().getUcId(), slot));
                    }


                    for (pair<string, Slot> slot: slots) {
                        if (slot.second.getWeekDay() == "Monday") {

                        } else if (slot.second.getWeekDay() == "Tuesday") {
                            weekdays[1].push_back(slot);
                        } else if (slot.second.getWeekDay() == "Wednesday") {
                            weekdays[2].push_back(slot);
                        } else if (slot.second.getWeekDay() == "Thursday") {
                            weekdays[3].push_back(slot);
                        } else if (slot.second.getWeekDay() == "Friday") {
                            weekdays[4].push_back(slot);
                        }
                    }
                }

                cout << endl << "The student's schedule is:" << endl;
                for (int i = 0; i < weekdays.size(); i++) {
                    cout << weekdaysNames[i] << ": " << endl;
                    for (pair<string, Slot> slot: weekdays[i]) {
                        cout << slot.first << " " << decimalToHours(slot.second.getBeginTime()) << " to " << decimalToHours(slot.second.getEndTime())
                        << " " << slot.second.getType() << endl;
                    }
                }
                cout << "Press q to go back to the menu" << endl;
                string q;
                cin >> q;
                break;
        }
            case 8:
                return 0;
            default:
                cout << "Please choose a valid option" << endl;
                break;
        }
    }
}
