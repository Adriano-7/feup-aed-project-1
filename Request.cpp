#include "Request.h"


/**
* @brief Constructor of the Request class. If the type of Request is not valid, it type is set to be empty string.
* @details Time complexity: O(1)
* @param student Student that made the request
* @param desiredClass Class that the student wants to enroll in
*/
Request::Request(const Student &student, const UcClass &desiredClass, const string &type) {
    if(type != "Changing" && type != "Removal" && type != "Enrollment") return;
    this->student = student;
    this->desiredUcClass = desiredClass;
    this->type = type;
}

/**
 * @brief Prints the header of the request (student name, student number, if type is removal -> Requested Uc, else requested class)
 * @details Time complexity: O(1)
 */

void Request::printHeader() const{
    cout << "Student: " << student.getName() << " - "<< student.getId() <<  "  |  ";
    if(type == "Removal") cout << "Requested Uc: " << desiredUcClass.getUcId();
    else{
        cout << "Requested class: " << desiredUcClass.getUcId() << " - " << desiredUcClass.getClassId();
    }
}

/**
 * @brief Prints the request
 * @details calls printHeader() and then prints the type of the request
 * Time complexity: O(1)
 */
void Request::print() const {
    printHeader();
    cout << "  |  " << "Type: " << type << endl;
}

/**
* @brief Returns the student that made the request
* @details Time complexity: O(1)
* @return Student that made the request
*/
Student Request::getStudent() const {
    return student;
}

/**
* @brief Returns the UcClass that the student wants to enroll in
* @details Time complexity: O(1)
* @return Class that the student wants to enroll in
*/
UcClass Request::getDesiredUcClass() const {
    return desiredUcClass;
}