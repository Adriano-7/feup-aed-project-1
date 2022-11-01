#include "App.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>
#include <unistd.h>

using namespace std;


App::App(const ScheduleManager &manager) {
    this->manager = manager;
    cout << ">> Schedule manager is online" << endl;
}


/**
 * @brief Function that prints the main menu
 */
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


void App::waitForInput() const{
    string q;
    cout << endl << "Insert any key to go back to the menu: ";
    cin >> q;
    cout << endl;
    system("clear");
}

/**
 * @brief Function that checks the schedule of a student
 */
void App::checkStudentSchedule() const {
    string upNumber;
    cout << "Please insert the student's UP number: ";
    cin >> upNumber;
    manager.printStudentSchedule(upNumber);
    waitForInput();
}

/**
 * @brief Function that checks the schedule of a class
 */
void App::checkClassSchedule() const{
    string classCode;
    cout << "Please insert the class code: "; cin >>classCode; cout<<endl;
    manager.printClassSchedule(classCode);
    waitForInput();
}

/**
 * @brief Function that checks the students in a class of a certain subject
 *
 */
void App::checkClassStudents() const{
    string ucCode, classCode;
    cout << "Please insert the subject code: "; cin >> ucCode;
    cout << "Please insert the class code: "; cin >> classCode; cout << endl;
    ClassSchedule* cs = manager.findSchedule(UcClass(ucCode, classCode));
    if(cs == nullptr){
        cout << ">> Class not found" << endl;
        usleep(900000);
        return;
    }
    cs->printStudents();
    waitForInput();
}

/**
 * @brief Function that checks the schedule of a subject
 */
void App::checkUcSchedule() const {
    string subjectCode;
    cout << "Insert the subject code: "; cin >> subjectCode; cout << endl;
    manager.printUcSchedule(subjectCode);
}

/**
 * @brief Function that submits a changing request
 */
void App::submitNewRequest() {
    string upNumber, ucCode, classCode;
    cout << "Please insert the student's UP number: ";
    cin >> upNumber;
    cout << endl;
    Student *student = manager.findStudent(upNumber);
    if (student == nullptr) {
        cout << ">> Student not found." << endl;
        usleep(900000);
        waitForInput();
    }
    student->print();
    cout << "The following information is related to the class you want to change to, "
            "for a certain curricular unit." << endl;
    cout << "Please insert the subject code: ";
    cin >> ucCode;
    cout << "Please insert the class code: ";
    cin >> classCode;
    ClassSchedule *cs = manager.findSchedule(UcClass(ucCode, classCode));
    if (cs == nullptr) {
        cout << ">> Class not found." << endl;
        usleep(900000);
        waitForInput();
        return;
    }
    manager.addRequest(*student, cs->getUcClass());
    cout << ">> Request submitted successfully." << endl;
    usleep(900000);
    waitForInput();
}


/**
 * @brief Function that runs the application
 * @return 0 if the application was closed successfully
 */

int App::run() {
    manager.readFiles();

    while (true) {
        system("clear");
        int option = optionsMenu();
        switch (option) {
            case 1: {
                checkStudentSchedule();
                break;
            }
            case 2: {
                checkClassSchedule();
                break;
            }
            case 3: {
                checkClassStudents();
                break;
            }
            case 4: {
                checkUcSchedule();
                break;
            }
            case 5: {
                submitNewRequest();
                break;
            }
            case 6:
                return 0;
            default:
                cout << ">> Please choose a valid option" << endl;
                usleep(900000);
                break;
        }
    }
}

