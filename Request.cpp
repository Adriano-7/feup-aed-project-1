#include "Request.h"

Request::Request(const Student &student, const UcClass &desiredClass){
    this->student = student;
    this->desiredClass = desiredClass;
}

Student Request::getStudent() const {
    return student;
}

UcClass Request::getDesiredClass() const {
    return desiredClass;
}

void Request::print() const {
    cout << "Student: " << student.getName() << " - "<< student.getId() << endl;
    cout << "Requested class: " << desiredClass.getUcId() << " - " << desiredClass.getClassId() << endl;
}