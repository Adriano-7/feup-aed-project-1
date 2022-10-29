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
    cout << endl << "Insert any key to go back to the menu: ";
    cin >> q;
    cout << endl;
    system("clear");
}

void App::option1() {
    string upNumber;
    cout << "Please insert the student's up number: ";
    cin >> upNumber;
    manager.printStudentSchedule(upNumber);
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
