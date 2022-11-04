#include "Request.h"


/**
* @brief Constructor of the Request class
* @param student Student that made the request
* @param desiredClass Class that the student wants to enroll in
*/
Request::Request(const Student &student, const UcClass &desiredClass, const string &type) {
    if(type != "Changing" && type != "Removal" && type != "Enrollment") return;
    this->student = student;
    this->desiredClass = desiredClass;
    this->type = type;
}

void Request::printHeader() const{
    cout << "Student: " << student.getName() << " - "<< student.getId() <<  "  |  ";
    if(type == "Removal") cout << "Requested subject: " << desiredClass.getUcId();
    else{
        cout << "Requested class: " << desiredClass.getUcId() << " - " << desiredClass.getClassId();
    }
}

/**
 * @brief Prints the request
*/
void Request::print() const {
    printHeader();
    cout << "  |  " << "Type: " << type << endl;
}

/**
* @brief Getter of the student that made the request
* @return Student that made the request
*/
Student Request::getStudent() const {
    return student;
}

/**
* @brief Getter of the class that the student wants to enroll in
* @return Class that the student wants to enroll in
*/
UcClass Request::getDesiredClass() const {
    return desiredClass;
}