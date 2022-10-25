#include "UcClass.h"
#include <iostream>

UcClass::UcClass() {

}

UcClass::UcClass(string ucId, string classId) {
    this->ucId = ucId;
    this->classId = classId;
}

string UcClass::getUcId() const {
    return ucId;
}

string UcClass::getClassId() const {
    return classId;
}

bool UcClass::operator ==(const UcClass &other) const {
    return this->ucId == other.ucId && this->classId == other.classId;
}

