//
// Created by evans24 on 27-10-2022.
//

#include "App.h"
#include "Test.h"
#include <iostream>

using namespace std;

App::App(ScheduleManager manager) {
    this->manager = manager;
    cout << "Schedule manager is online" << endl << endl;
}

void App::run() {
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
            case 1:
                cout << "HEELLLO" << endl;
                break;
        }
    }



}

