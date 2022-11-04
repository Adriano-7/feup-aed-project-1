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
            << "6 Submit a request" << endl
            << "7 Print pending requests" << endl
            << "8 Process requests" << endl
            << "9 Exit" << endl
            << "What would you like to do next? " ;
    cin >> option; cout << endl;
    if (cin.fail()) {
        throw invalid_argument(">> Invalid number");
    }
    while(option < 1 || option > 9) {
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    return option;
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
            case 6:{
                int i = requestsMenu();
                if(i != 4) {
                    submitNewRequest(i);
                }
                break;
            }
            case 7: {
                printPendingRequests();
                break;
            }
            case 8:{
                processPendingRequests();
                break;
            }
            case 9: {
                saveInformation();
                return 0;
            }
            default:
                cout << ">> Invalid option." << endl;
        }
    }
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

int App::sortingMenu() const {
    cout << "1 Alphabetical" << endl;
    cout << "2 Alphabetical in reverse" << endl;
    cout << "3 Numerical" << endl;
    cout << "4 Numerical in reverse" << endl;
    cout << "In which order do you want to display the students? ";
    int option; cin >> option; cout << endl;
    if(cin.fail())
        throw invalid_argument(">> Invalid number");
    while(option < 1 || option > 4){
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    return option;
}
/**
* @brief Asks the user to insert the ucCode and classCode and prints the students enrolled
*/
void App::checkClassStudents() const {
    int option = sortingMenu();
    string ucCode, classCode;
    cout << "Please insert the subject code: ";
    cin >> ucCode;
    cout << "Please insert the class code: ";
    cin >> classCode;
    cout << endl;
    UcClass ucClass = UcClass(ucCode, classCode);
    switch (option) {
        case 1:
            manager.printClassStudents(ucClass, "alphabetical");
            break;
        case 2:
            manager.printClassStudents(ucClass, "reverse alphabetical");
            break;
        case 3:
            manager.printClassStudents(ucClass, "numerical");
            break;
        case 4:
            manager.printClassStudents(ucClass, "reverse numerical");
            break;
        default:
            cout << ">> Invalid option." << endl;
    }
}

/**
* @brief Asks the user to insert the ucId and prints the schedule of that subject
*/
void App::checkUcSchedule() const {
    string subjectCode;
    cout << "Insert the subject code: "; cin >> subjectCode; cout << endl;
    manager.printUcSchedule(subjectCode);
}

int App::requestsMenu() const {
    int option;
    cout << "There are 3 types of requests:" << endl;
    cout << "1 - Change class" << endl;
    cout << "2 - Enroll in a new subject" << endl;
    cout << "3 - Cancel a subject registration" << endl;
    cout << "4 - Go back" << endl;
    cout << "What type of request do you want to submit? ";
    cin >> option;
    if (cin.fail()) {
        throw invalid_argument(">> Invalid number");
    }
    while(option < 1 || option > 4) {
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    return option;
}

void App::submitChangingRequest(Student* student) {
    string ucCode, classCode;
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
    manager.addChangingRequest(*student, UcClass(ucCode, classCode));
    cout << ">> Request submitted successfully." << endl;
}

void App::submitEnrollmentRequest(Student *student) {
    string ucCode, classCode;
    cout << endl << "The following information is related to the subject and the class you want to enroll in." << endl;
    cout << "Please insert the subject code: ";
    cin >> ucCode;
    if(student->isEnrolled(ucCode)){
        cout << ">> This student is already enrolled in this subject." << endl;
        return;
    }
    cout << "Please insert the class code: ";
    cin >> classCode;
    ClassSchedule *cs = manager.findSchedule(UcClass(ucCode, classCode));
    if (cs == nullptr) {
        cout << ">> Class not found." << endl;
        return;
    }
    manager.addEnrollmentRequest(*student, UcClass(ucCode, classCode));
    cout << ">> Request submitted successfully." << endl;
}

void App::submitRemovalRequest(Student *student) {
    string ucCode;
    cout << endl << "The following information is related to the subject you want to remove." << endl;
    cout << "Please insert the subject code: ";
    cin >> ucCode;
    if(!student->isEnrolled(ucCode)){
        cout << ">> This student is not enrolled in this subject." << endl;
        return;
    }
    for(UcClass &i : student->getClasses()){
        if(i.getUcId() == ucCode){
            manager.addRemovalRequest(*student, i);
            cout << ">> Request submitted successfully." << endl;
            return;
        }
    }
    cout << ">> Request submitted successfully." << endl;
}


/**
* @brief Function that allows the student to submit a request to change a class
*/
void App::submitNewRequest(int option) {
    string upNumber;
    cout << "Please insert the student's UP number: ";
    cin >> upNumber;
    cout << endl;
    Student *student = manager.findStudent(upNumber);
    if (student == nullptr) {
        cout << ">> Student not found." << endl;
        return;
    }
    student->print();
    switch (option) {
        case 1:
            submitChangingRequest(student);
            break;
        case 2:
            submitEnrollmentRequest(student);
            break;
        case 3:
            submitRemovalRequest(student);
            break;
        default:
            cout << ">> Invalid option." << endl;
    }
}
/**
* @brief Function that prints the students enrolled in a uc
*/
void App::checkUcStudents() const{
    int option = sortingMenu();
    string ucCode;
    cout << "Please insert the subject code: "; cin >> ucCode;
    switch (option) {
        case 1:
            manager.printUcStudents(ucCode, "alphabetical");
            break;
        case 2:
            manager.printUcStudents(ucCode, "reverse alphabetical");
            break;
        case 3:
            manager.printUcStudents(ucCode, "numerical");
            break;
        case 4:
            manager.printUcStudents(ucCode, "reverse numerical");
            break;
        default:
            cout << ">> Invalid option." << endl;
    }
}
/**
 * @brief Function that processes all pending changingRequests
 */
void App::processPendingRequests() {
    string s;
    cout << "Do you want to see all pending changingRequests first? (y/n) "; cin >> s; cout << endl;
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

void App::printPendingRequests() const {
    manager.printPendingRequests();
}