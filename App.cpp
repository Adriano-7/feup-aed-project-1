#include "App.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <unistd.h>

using namespace std;

/**
* @brief Constructor, sleepTime is set to 800000 ms
* @details Time complexity: O(1)
* @param ScheduleManager manager
*/
App::App(const ScheduleManager &manager) {
    this->manager = manager;
    this->sleepTime = 800000;
}

/**
* @brief Function that prints the main menu
* @return the option chosen by the user
*/
int App::optionsMenu() const {

    int option;
    cout    << endl << "----------------------- OPTIONS -----------------------" << endl <<"\n"
                    << "1 Check the schedule of a student" << endl
                    << "2 Check the schedule of a class" << endl
                    << "3 Check the schedule of a uc"<< endl
                    << "4 Check the students enrolled in a class of a given uc"<< endl
                    << "5 Check the students enrolled in a uc" << endl
                    << "6 Submit a request" << endl
                    << "7 Print pending requests" << endl
                    << "8 Process requests" << endl
                    << "9 Exit" << endl << "\n"
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
    system("clear");
    manager.readFiles();

    while (true) {
        system("clear");
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
 * @details Time complexity: O(log p) + O(hlog n) + O(hl*log(r*log(c)) + O(cd)
 * where p is the number of lines in students_classes.csv,  h is the number of classes of the student,
 * n is the number of students, l is the number of slots in a given ClassSchedule, r is the number of slots in a weekday,
 * c is the number of slots in a weekday and d is the number of classes in a slot
*/
void App::checkStudentSchedule() const {
    string upNumber;
    cout << "Please insert the student's UP number: ";
    cin >> upNumber;
    manager.printStudentSchedule(upNumber);
}
/**
* @brief Ask the user to insert the class code and prints the schedule of that class
 * @details Time complexity: O(n*l*log(r*log(c)) + O(cd) where n is the number of schedules,
 * l is the number of slots in a schedule, c is the number of slots in a weekday,
 * r is the number of weekdays and d is the number of classes in a slot
*/
void App::checkClassSchedule() const{
    string classCode;
    cout << "Please insert the class code: "; cin >>classCode; cout<<endl;
    manager.printClassSchedule(classCode);
}

/**
 * @brief Ask the user to insert the sorting option
 * @return sorting option
 */
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
 * @details Time complexity: O(log n) + O(q log q) where n is the number of schedules(lines classes_per_uc.csv)
 * and q is the number of students in the ClassSchedule
*/
void App::checkClassStudents() const {
    int option = sortingMenu();
    string ucCode, classCode;
    cout << "Please insert the uc code: ";
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
* @brief Asks the user to insert the ucId and prints the schedule of that uc
 * @details Time complexity: O(n*l*log(r*log(c)) + O(cd) where n is the number of schedules,
 * l is the number of slots in a schedule, c is the number of slots in a weekday,
 * r is the number of weekdays and d is the number of classes in a slot
*/
void App::checkUcSchedule() const {
    string ucCode;
    cout << "Insert the uc code: "; cin >> ucCode; cout << endl;
    manager.printUcSchedule(ucCode);
}

/**
 * @brief Asks the user to insert the type of request
 * @details Time complexity: O(1)
 */
int App::requestsMenu() const {
    system("clear");
    int option;
    cout << "There are 3 types of requests:" << endl;
    cout << "1 - Change class" << endl;
    cout << "2 - Enroll in a new uc" << endl;
    cout << "3 - Cancel a uc registration" << endl;
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

/**
 * @brief Asks the user to insert the class code he wants to change into
 * @details Time complexity: O(log n) where n is the number of schedules(lines file classes_per_uc.csv)
 */
void App::submitChangingRequest(Student* student) {
    string ucCode, classCode;
    cout << endl << "The following information is related to the class you want to change to, "
                    "for a certain curricular unit." << endl;
    cout << "Please insert the uc code: ";
    cin >> ucCode;
    if(!student->isEnrolled(ucCode)){
        cout << ">> This student is not enrolled in this uc." << endl;
        waitForInput();
        return;
    }
    cout << "Please insert the class code: ";
    cin >> classCode;
    ClassSchedule *cs = manager.findSchedule(UcClass(ucCode, classCode));
    if (cs == nullptr) {
        cout << ">> Class not found." << endl;
        waitForInput();
        return;
    }
    manager.addChangingRequest(*student, UcClass(ucCode, classCode));
    cout << ">> Request submitted successfully." << endl;
    waitForInput();
}

/**
 * @brief Asks the user to insert the uc code he wants to enroll into
 * @details Time complexity: O(log n) where n is the number of schedules(lines file classes_per_uc.csv)
 */
void App::submitEnrollmentRequest(Student *student) {
    string ucCode, classCode;
    cout << endl << "The following information is related to the uc and the class you want to enroll in." << endl;
    cout << "Please insert the uc code: ";
    cin >> ucCode;
    if(student->isEnrolled(ucCode)){
        cout << ">> This student is already enrolled in this uc." << endl;
        waitForInput();
        return;
    }
    cout << "Please insert the class code: ";
    cin >> classCode;
    ClassSchedule *cs = manager.findSchedule(UcClass(ucCode, classCode));
    if (cs == nullptr) {
        cout << ">> Class not found." << endl;
        waitForInput();
        return;
    }
    manager.addEnrollmentRequest(*student, UcClass(ucCode, classCode));
    cout << ">> Request submitted successfully." << endl;
    waitForInput();
}

/**
 * @brief Asks the user to insert the uc code he wants to cancel
 * @details Time complexity: O(t) where t is the number of UcClasses of the student
 */
void App::submitRemovalRequest(Student *student) {
    string ucCode;
    cout << endl << "The following information is related to the uc you want to remove." << endl;
    cout << "Please insert the uc code: ";
    cin >> ucCode;
    if(!student->isEnrolled(ucCode)){
        cout << ">> This student is not enrolled in this uc." << endl;
        waitForInput();
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
    waitForInput();
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
        waitForInput();
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
 * @details Time complexity: Time complexity O(n)+ O(jq) + O(d log d) where n is the number of schedules(lines in classes_per_uc.csv file),
 * j the number of ClassSchedules with a given ucId, q the number of students in a given ClassSchedule cs and d is the number of students in a given uc
*/
void App::checkUcStudents() const{
    int option = sortingMenu();
    string ucCode;
    cout << "Please insert the uc code: "; cin >> ucCode;
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
 * @details Time complexity: Time complexity: O(h) + O(log n * log n) + O(log p) + O(t*log n + t*lr) + O(nlog n) where n is the number of schedules (lines in the classes_per_uc.csv file),
 * p is the number of lines in the students.csv file, h is the number of classes of the student submitting the request,
 * t is the number of classes the student is enrolled in, n is the number of lines in classes_per_uc.csv, l is the number of slots of the first class
 */
void App::processPendingRequests() {
    if(manager.getNumberOfPendingRequests() == 0){
        cout << ">> There are no pending requests." << endl;
        waitForInput();
        return;
    }
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
 * @details Time complexity: O(O(st) where s is the number of students in the set and t is the number of classes of each student)
 */
void App::saveInformation() {
    manager.writeFiles();
}

/**
* @brief Function that makes the program wait for user input to continue
 * @details Time complexity: O(1)
*/
void App::waitForInput() const{
    usleep(sleepTime);
    string q;
    cout << endl << "Insert any key to continue: ";
    cin >> q;
    cout << endl;
    system("clear");
}

/**
 * @brief Function to print the pending requests
 * @details Time complexity: Time complexity: O(v)+O(w)+O(z) where v is the number of removal request, w is the number of changing requests and z is the number of enrollment requests
 */
void App::printPendingRequests() const {
    if(manager.getNumberOfPendingRequests() == 0){
        cout << ">> There are no pending requests." << endl;
        waitForInput();
        return;
    }
    manager.printPendingRequests();
    waitForInput();
}