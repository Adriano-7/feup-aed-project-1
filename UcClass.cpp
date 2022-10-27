#include "UcClass.h"

UcClass::UcClass() {
    this->ucId = "";
    this->classId = "";
    this->numStudents=0;
}

UcClass::UcClass(string ucId, string classId) {
    this->ucId = ucId;
    this->classId = classId;
    this->numStudents=0;
}

void UcClass::setNumStudents(int numStudents){
    this->numStudents=numStudents;
}
int UcClass::getNumStudents() const{
    return this->numStudents;
}

string UcClass::getUcId() const {
    return ucId;
}

string UcClass::getClassId() const {
    return classId;
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

bool UcClass::sameUC(UcClass other) const {
    return this->ucId == other.ucId;
}