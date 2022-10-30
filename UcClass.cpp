#include "UcClass.h"

UcClass::UcClass() {
    this->ucId = "";
    this->classId = "";
}

UcClass::UcClass(const string &ucId, const string &classId) {
    this->ucId = ucId;
    this->classId = classId;
}

string UcClass::getUcId() const {
    return ucId;
}

string UcClass::getClassId() const {
    return classId;
}

bool UcClass::sameUC(const UcClass &other) const {
    return this->ucId == other.ucId;
}

bool UcClass::operator == (const UcClass &other) const {
    return this->ucId == other.ucId && this->classId == other.classId;
}

bool UcClass::operator < (const UcClass &other) const {
    if(this->ucId == other.ucId) return this->classId < other.classId;
    return this->ucId < other.ucId;
}

bool UcClass::operator > (const UcClass &other) const {
    if(this->ucId == other.ucId) return this->classId > other.classId;
    return this->ucId > other.ucId;
}
