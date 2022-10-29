#include "App.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>
#include <unistd.h>

using namespace std;

App::App(ScheduleManager manager) {
    this->manager = manager;
    cout << ">> Schedule manager is online" << endl;
}

int App::optionsMenu() {
    int option;
    cout    << endl << "------------ OPTIONS ------------" << endl
            << "1 Check the schedule of a student" << endl
            << "2 Check the schedule of a class" << endl
            << "3 Check the students in class " << endl
            << "4 Check the schedule of a subject "<< endl
            << "5 Submit a changing request" << endl
            << "6 Exit" << endl
            << "What would you like to do next? " ;
    cin >> option;
    cout << endl;
    if (cin.fail()) {
        throw invalid_argument(">> Please choose a valid number");
    }
    if(option < 1 || option > 8) {
        return 0;
    }
    return option;
}

void App::waitForInput() {
    string q;
    cout << endl << "Insert any key to go back to the menu: "; cin >> q;cout << endl;system("clear");
}

string decimalToHours(int decimal){
    double time = decimal;
    int timeMins = (int)floor( time * 60.0 );
    int hours = timeMins / 60;
    int minutes = timeMins % 60;
    string hoursStr = to_string(hours);
    string minutesStr = to_string(minutes);
    if (hours < 10) hoursStr = "0" + hoursStr;
    if (minutes < 10) minutesStr = "0" + minutesStr;
    return hoursStr + ":" + minutesStr;
}


void App::checkStudentSchedule() {
    system("clear");
    string upNumber;
    cout << "Please insert the student's UP number: ";
    cin >> upNumber;

    Student student = Student(upNumber, "");

    auto loc = manager.getStudents().find(student);
    if (loc == manager.getStudents().end()) {
        system("clear");
        cout << ">> Student not found" << endl;
        return;
    }

    student = *loc;

    vector<UcClass> studentClasses = student.getClasses();
    vector<vector<pair<string, Slot>>> weekdays = vector<vector<pair<string, Slot>>>(5);
    vector<string> weekdaysNames = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    system("clear");
    cout << endl <<  ">> The student " << student.getName() << " with UP number " << student.getId()
         << " is enrolled in the following classes:" << endl;
    for (UcClass classs: studentClasses) {
        cout << "   " << classs.getUcId() << " " << classs.getClassId() << "  |  ";
    }
    cout << endl;

    for (UcClass ucClass: studentClasses) {
        ClassSchedule cs = manager.getSchedules()[manager.binarySearchSchedules(ucClass)];
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

    cout << endl << ">> The student's schedule is:" << endl;
    for (int i = 0; i < weekdays.size(); i++) {
        sort(weekdays[i].begin(), weekdays[i].end(), [](pair<string, Slot> a, pair<string, Slot> b) {
            return a.second.getStartTime() < b.second.getStartTime();
        });
        cout << "   >> "<< weekdaysNames[i] << ": " << endl;

        for (pair<string, Slot> slot: weekdays[i]) {
            cout << "      " << slot.first << "   " << decimalToHours(slot.second.getStartTime()) << " to " << decimalToHours(slot.second.getEndTime())
                 << "   " << slot.second.getType() << endl;
        }
    }
    waitForInput();
}

void App::checkClassSchedule(){
    system("clear");
    cout << ">> This feature is not available yet" << endl;
}

void App::checkClassStudents(){
    system("clear");
    string ucCode, classCode;
    cout << "Please insert the UC code: "; cin >> ucCode;
    cout << "Please insert the class code: "; cin >> classCode; cout << endl;
    int index = manager.binarySearchSchedules(UcClass(ucCode, classCode));
    if(index == -1){
        cout << ">> Class not found" << endl;
        return;
    }
    ClassSchedule cs = manager.getSchedules()[index];
    cs.printStudents();
    waitForInput();
}

void App::checkUcSchedule(){
    system("clear");
    cout << ">> This feature is not available yet" << endl;
}

void App::submitNewRequest(){
    system("clear");
    string upNumber, ucCode, classCode;
    cout << "Please insert the student's UP number: "; cin >> upNumber; cout << endl;
    if(!manager.studentExists(upNumber)){
        cout << ">> Student not found." << endl;
        waitForInput();
        return;
    }
    cout << "The following information is related to the class you want to change to, "
            "for a certain curricular unit." << endl;
    cout << "Please insert the UC code: "; cin >> ucCode;
    cout << "Please insert the class code: "; cin >> classCode;
    if(!manager.ucClassExists(ucCode, classCode)){
        cout << ">> Class not found." << endl;
        waitForInput();
        return;
    }
    Student student = Student(upNumber, "");
    UcClass ucClass = UcClass(ucCode, classCode);
    manager.addRequest(student, ucClass);
    cout << endl << ">> Request successfully submitted!" << endl;
    waitForInput();
}

int App::run() {
    manager.readFiles();
    system("clear");

    while (true) {
        int option = optionsMenu();
        switch (option) {
            case 1:{
                checkStudentSchedule();
                break;
            }
            case 2:{
                checkClassSchedule();
                break;
            }
            case 3:{
                checkClassStudents();
                break;
            }
            case 4:{
                checkUcSchedule();
                break;
            }
            case 5:{
                submitNewRequest();
                break;
            }
            case 6:
                return 0;
            default:
                system("clear");
                cout << ">> Please choose a valid option" << endl;
                usleep(900000);
                break;
            }
    }
}
