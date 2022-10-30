#include "App.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

App::App(ScheduleManager manager) {
    this->manager = manager;
    cout << ">> Schedule manager is online" << endl;
}

void App::waitForInput() {
    string q;
    cout << endl << "Insert any key to go back to the menu: "; cin >> q;cout << endl;system("clear");
}

void insertIntoWeek(vector<vector<pair<string, Slot>>> &weekdays , vector<pair<string, Slot>> slots){
    for (pair<string, Slot> slot: slots) {

       if (slot.second.getWeekDay() == "Monday") {
              weekdays[0].push_back(slot);
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
void groupDuplicates(vector<vector<pair<string, Slot>>> &weekdays){
    for (int i = 0; i < weekdays.size(); i++) {
        for (int j = 0; j < weekdays[i].size(); j++) {
            for (int k = j + 1; k < weekdays[i].size(); k++) {
                if (weekdays[i][j].second == weekdays[i][k].second) {
                    weekdays[i][j].first += ", " + weekdays[i][k].first;
                    weekdays[i].erase(weekdays[i].begin() + k);
                    k--;
                }
            }
        }
    }
}
string toString(vector<string> stringg){
    string s;
    for (string str: stringg){
        s += str + " ";
    }
    return s;
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
    Student modStudent = *loc;

    vector<UcClass> studentClasses = modStudent.getClasses();
    cout << endl <<  ">> The student " << modStudent.getName() << " with UP number " << modStudent.getId()
         << " is enrolled in the following classes:" << endl;
    for (UcClass classs: studentClasses) {
        cout << "   " << classs.getUcId() << " " << classs.getClassId() << "  |  ";
    }
    cout << endl;
    vector<vector<pair<string, Slot>>> weekdays = vector<vector<pair<string, Slot>>>(5);

    for (UcClass ucClass: studentClasses) {
        ClassSchedule cs = manager.getSchedules()[manager.binarySearchSchedules(ucClass)];
        vector<pair<string, Slot>> slots;
        for (Slot slot: cs.getSlots()) {
            slots.push_back(make_pair(cs.getUcClass().getUcId(), slot));
        }
        insertIntoWeek(weekdays, slots);
    }

    vector<string> weekdaysNames = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    cout << endl << ">> The student's schedule is:" << endl;
    for (int i = 0; i < weekdays.size(); i++) {
        sort(weekdays[i].begin(), weekdays[i].end(), [](pair<string, Slot> a, pair<string, Slot> b) {
            return a.second.getStartTime() < b.second.getStartTime();
        });
        cout << "   >> "<< weekdaysNames[i] << ": " << endl;

        for (pair<string, Slot> slot: weekdays[i]) {
            cout << "       " << slot.first << "   " << decimalToHours(slot.second.getStartTime()) << " to " << decimalToHours(slot.second.getEndTime())
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

void App::option4() {
    cout << "Inset the subject code: " << endl;
    string subjectCode;
    cin >> subjectCode;
    vector<ClassSchedule> schedules;
    for (ClassSchedule cs: manager.getSchedules()) {
        if (cs.getUcClass().getUcId() == subjectCode) {
            schedules.push_back(cs);
        }
    }
    vector<vector<pair<string, Slot>>> weekdays = vector<vector<pair<string, Slot>>>(5);
    vector<string> weekdaysNames = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    // Insert the slots into the weekdays vector
    for (auto it = schedules.begin(); it != schedules.end(); it++) {
        vector<pair<string, Slot>> slots;
        for (Slot slot: it->getSlots()) {
            slots.push_back(make_pair(it->getUcClass().getClassId(), slot));
        }

        insertIntoWeek(weekdays, slots);
        groupDuplicates(weekdays);
    }
    cout << endl << ">> This UC class is:" << endl;
    for (int i = 0; i < weekdays.size(); i++) {
        sort(weekdays[i].begin(), weekdays[i].end(), [](pair<string, Slot> a, pair<string, Slot> b) {
            return a.second.getStartTime() < b.second.getStartTime();
        });
        cout << "   >> " << weekdaysNames[i] << ": " << endl;

        for (pair<string, Slot> slot: weekdays[i]) {
            cout << "       " << slot.first << "   " << decimalToHours(slot.second.getStartTime()) << " to " << decimalToHours(slot.second.getEndTime())
                 << "   " << slot.second.getType() << endl;
        }
    }
}
void App::option5(){
    system("clear");
    cout << ">> This feature is not available yet" << endl;
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
