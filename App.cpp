#include "App.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <unistd.h>

using namespace std;

/**
* @brief Constructor, sleepTime is set to 800000 ms
* @param ScheduleManager manager
*/
App::App(const ScheduleManager &manager) {
    this->manager = manager;
    this->sleepTime = 800000;
    cout << ">> Schedule manager is online" << endl;
}

/**
* @brief Function that runs the application, it calls the menu and the functions to read the files
* @return 0 if the application was closed successfully
*/
int App::run() {
    manager.readFiles();

    while (true) {
        int option = optionsMenu();
        switch (option) {
            case 1: {
                checkStudentSchedule();
                waitForInput();
                break;
            }
            case 2: {
                checkClassSchedule();
                waitForInput();
                break;
            }
            case 3: {
                checkUcSchedule();
                waitForInput();
                break;
            }
            case 4: {
                checkClassStudents();
                waitForInput();
                break;
            }
            case 5: {
                checkUcStudents();
                waitForInput();
                break;
            }
            case 6:
                submitNewRequest();
                waitForInput();
                break;

            case 7: {
                processPendingRequests();
                waitForInput();
                break;
            }
            case 8: {
                saveInformation();
                return 0;
            }
            default:{
                cout << ">> Please choose a valid option" << endl;
                usleep(sleepTime);
                break;
            }
        }
    }
}

/**
* @brief Function that prints the main menu
* @return the option chosen by the user
*/
int App::optionsMenu() const {

    int option;
    cout    << endl << "-------------- OPTIONS --------------" << endl
            << "1 Check the schedule of a student" << endl
            << "2 Check the schedule of a class" << endl
            << "3 Check the schedule of a subject"<< endl
            << "4 Check the students in class"<< endl
            << "5 Check the students enrolled in a subject" << endl
            << "6 Submit a changing request" << endl
            << "7 Process changing requests" << endl
            << "8 Exit" << endl
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

/**
* @brief Asks the user to input the students's UP number and prints the schedule of that student
*/
void App::checkStudentSchedule() const {
    string upNumber;
    cout << "Please insert the student's UP number: ";
    cin >> upNumber;
    manager.printStudentSchedule(upNumber);
}
/**
* @brief Ask the user to insert the class code and prints the schedule of that class
*/
void App::checkClassSchedule() const{
    string classCode;
    cout << "Please insert the class code: "; cin >>classCode; cout<<endl;
    manager.printClassSchedule(classCode);
}
/**
* @brief Asks the user to insert the ucCode and classCode and prints the students enrolled
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
}

/**
* @brief Asks the user to insert the ucId and prints the schedule of that subject
*/
void App::checkUcSchedule() const {
    string subjectCode;
    cout << "Insert the subject code: "; cin >> subjectCode; cout << endl;
    manager.printUcSchedule(subjectCode);
}
/**
* @brief Function that allows the student to submit a request to change a class
*/
void App::submitNewRequest() {
    string upNumber, ucCode, classCode;
    cout << "Please insert the student's UP number: ";
    cin >> upNumber;
    cout << endl;
    Student *student = manager.findStudent(upNumber);
    if (student == nullptr) {
        cout << ">> Student not found." << endl;
        return;
    }
    student->print();
    cout << endl << "The following information is related to the class you want to change to, "
                    "for a certain curricular unit." << endl;
    cout << "Please insert the subject code: ";
    cin >> ucCode;
    if(!student->isEnrolled(ucCode)){
        cout << ">> This student is not enrolled in this subject." << endl;
        return;
    }
    cout << "Please insert the class code: ";
    cin >> classCode;
    ClassSchedule *cs = manager.findSchedule(UcClass(ucCode, classCode));
    if (cs == nullptr) {
        cout << ">> Class not found." << endl;
        return;
    }
    manager.addRequest(*student, UcClass(ucCode, classCode));
    cout << ">> Request submitted successfully." << endl;
}
/**
* @brief Function that prints the students enrolled in a subject
*/
void App::checkUcStudents() const{
    string ucCode;
    cout << "Please insert the subject code: "; cin >> ucCode;
    manager.printUcStudents(ucCode);
}
/**
 * @brief Function that processes all pending requests
 */
void App::processPendingRequests() {
    string s;
    cout << "Do you want to see all pending requests first? (y/n) "; cin >> s; cout << endl;
    if(s == "y" || s == "Y"){
        manager.printPendingRequests();
        waitForInput();
    }
    manager.processRequests();
}

/**
 * @brief Function that writes the information to the files before closing the program
 */
void App::saveInformation() {
    manager.writeFiles();
}

/**
* @brief Function that makes the program wait for user input to continue
*/
void App::waitForInput() const{
    usleep(sleepTime);
    string q;
    cout << endl << "Insert any key to continue: ";
    cin >> q;
    cout << endl;
    system("clear");
}