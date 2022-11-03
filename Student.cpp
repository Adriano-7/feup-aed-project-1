#include "Student.h"
#include <string>
#include <iostream>

using namespace std;
/**
 * @brief Class constructor that sets the id, name of the student and classes vector empty
 *
 */
Student::Student() {
    this->id = "";
    this->name = "";
    this->classes = vector<UcClass>();
}
/**
 * @brief Class constructor that receives all the parameters
 *
 */
Student::Student(const string &id, const string &name) {
    this->id = id;
    this->name = name;
    this->classes = vector<UcClass>();
}
/** @brief Adds a class to the student
 */
void Student::addClass(const UcClass &newClass) {
    classes.push_back(newClass);
}
/** @brief Changes a class of the student
 * @return The class that was changed
 */
UcClass Student::changeClass(const UcClass &newClass) {
    for (int i = 0; i < classes.size(); i++) {
        if (classes.at(i).getUcId() == newClass.getUcId()) {
            UcClass oldClass = classes.at(i);
            classes.at(i) = newClass;
            return oldClass;
        }
    }
    return UcClass();
}

/** @brief Getter of the id
 * @return id
 */
string Student::getId() const {
    return id;
}
/** @brief Getter of the name
 * @return name
 */
string Student::getName() const {
    return name;
}
/** @brief Getter of the classes
 * @return classes
 */
vector <UcClass> Student::getClasses() const {
    return classes;
}

bool Student::isEnrolled(const string &ucCode) const {
    for (auto &i : classes) {
        if (i.getUcId() == ucCode) {
            return true;
        }
    }
    return false;
}

/** @brief Checks if two students have the same ID
 * @param other Student to compare
 * @return true if they have, false otherwise
 */
bool Student::operator==(const Student &other) const{
    return this->id == other.getId();
}
/** @brief Checks if a student id is less than another
 * @param other Student to compare
 * @return true if it is less than, false otherwise
 */
bool Student::operator<(const Student &other) const {
    return this->id < other.getId();
}
/** @brief Checks if a student id is greater than another
 * @param other Student to compare
 * @return true if it is greater than, false otherwise
 */
bool Student::operator>(const Student &other) const {
    return this->id > other.getId();
}
/** @brief Prints the header of the student
 */
void Student::printHeader() const {
    cout << name << " - " << id << endl;
}
/** @brief Prints the classes of the student
 */
void Student::printClasses() const {
    int i = 0;
    while(i < classes.size()-1){
        cout << classes[i].getUcId() << " " << classes[i].getClassId() << "  |  ";
        i++;
    }
    cout << classes[i].getUcId() << " " << classes[i].getClassId() << endl;
}

/** @brief Prints the student
 */
void Student::print() const {
    cout << "Student: "; printHeader();
    cout << "Classes: "; printClasses();
}