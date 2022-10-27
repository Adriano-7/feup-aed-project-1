#include "Request.h"

Request::Request(Student student, UcClass desiredClass){
    this->student = student;
    this->desiredClass = desiredClass;
}

Student Request::getStudent() const {
    return student;
}

UcClass Request::getDesiredClass() const {
    return desiredClass;
}
