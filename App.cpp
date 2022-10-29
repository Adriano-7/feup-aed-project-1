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

int App::run() {
    manager.readFiles();
    system("clear");

    while (true) {
        int option = optionsMenu();
        switch (option) {
            case 1:{
                option1();
                break;
            }
            case 2:{
                option2();
                break;
            }
            case 3:{
                option3();
                break;
            }
            case 4:{
                option4();
                break;
            }
            case 5:{
                option5();
                break;
            }
            case 6:
                return 0;
            default:
                system("clear");
                cout << ">> Please choose a valid option" << endl;
                break;
        }
    }
}

int App::optionsMenu() {
    int option;
    cout    << endl << "------------ OPTIONS ------------" << endl
            << "1 Check the schedule of a student" << endl
            << "2 Check the schedule of a class" << endl
            << "3 Check the students in class " << endl
            << "4 Check the schedule of a subject "<< endl
            << "5 Make a changing request" << endl
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

void App::option1() {
    string upNumber;
    cout << "Please insert the student's up number: ";
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

void App::option2(){
    system("clear");
    cout << ">> This feature is not available yet" << endl;
}

void App::option3(){
    string ucCode, classCode;
    cout << "Please insert the UC code: "; cin >> ucCode;
    cout << "Please insert the class code: "; cin >> classCode; cout << endl;
    UcClass ucClass = UcClass(ucCode, classCode);
    int index = manager.binarySearchSchedules(ucClass);
    if(index == -1){
        cout << ">> Class not found" << endl;
        return;
    }
    ClassSchedule cs = manager.getSchedules()[index];
    cs.printStudents();
    waitForInput();
}

void App::option4(){
    system("clear");
    cout << ">> This feature is not available yet" << endl;
}
void App::option5(){
    system("clear");
    cout << ">> This feature is not available yet" << endl;
}
