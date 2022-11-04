#include "Student.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
/**
 * @brief Class constructor that sets the id, name of the student and classes vector empty
 * @details Time complexity: O(1)
 */
Student::Student() {
    this->id = "";
    this->name = "";
    this->classes = vector<UcClass>();
}
/**
 * @brief Class constructor that receives all the parameters
 * @details Time complexity: O(1)
 */
Student::Student(const string &id, const string &name) {
    this->id = id;
    this->name = name;
    this->classes = vector<UcClass>();
}
/** @brief Adds a class to the student
 *  @details Time complexity: O(1)
 */
void Student::addClass(const UcClass &newClass) {
    classes.push_back(newClass);
}
/** @brief Changes a class of the student
 *  @details Time complexity: O(n)
 *  @return The class that was changed
 */
UcClass Student::changeClass(const UcClass &newClass) {
    for (int i = 0; i < classes.size(); i++) {
        if (classes.at(i).getUcId() == newClass.getUcId()) {
            UcClass oldClass = classes.at(i);
            classes.at(i) = newClass;
            return oldClass;
        }
    }
    return {};
}

/** @brief Removes a uc from the student
 *  @details Time complexity: O(n)
 */
void Student::removeUc(const string &ucCode) {
    for (int i = 0; i < classes.size(); i++) {
        if (classes.at(i).getUcId() == ucCode) {
            classes.erase(classes.begin() + i);
            return;
        }
    }
}

/** @brief Adds a uc to the student
 *  @details Time complexity: O(nlogN)
 */
void Student::addUc(const UcClass &newClass) {
    classes.push_back(newClass);
    sort(classes.begin(), classes.end());
}

/** @brief Checks if the student is enrolled in a given UC
 * @details Time complexity: O(n)
 * @param ucCode UC code to check
 * @return true if the student is enrolled, false otherwise
 */
bool Student::isEnrolled(const string &ucCode) const {
    for (auto &i : classes) {
        if (i.getUcId() == ucCode) {
            return true;
        }
    }
    return false;
}

/** @brief Prints the header of the student
 * @details Time complexity: O(1)
 */
void Student::printHeader() const {
    cout << name << " - " << id << endl;
}

/** @brief Prints the classes of the student
 * @details Time complexity: O(n)
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
 * @details Time complexity: O(n)
 */
void Student::print() const {
    cout << "Student: "; printHeader();
    cout << "Classes: "; printClasses();
}

/** @brief Getter of the id
 * @details Time complexity: O(1)
 * @return id
 */
string Student::getId() const {
    return id;
}
/** @brief Getter of the name
 * @details Time complexity: O(1)
 * @return name
 */
string Student::getName() const {
    return name;
}
/** @brief Getter of the classes
 * @details Time complexity: O(1)
 * @return classes
 */
vector <UcClass> Student::getClasses() const {
    return classes;
}

/** @brief Checks if two students have the same ID
 * @details Time complexity: O(1)
 * @param other Student to compare
 * @return true if they have, false otherwise
 */
bool Student::operator==(const Student &other) const{
    return this->id == other.getId();
}
/** @brief Checks if a student id is less than another
 * @details Time complexity: O(1)
 * @param other Student to compare
 * @return true if it is less than, false otherwise
 */
bool Student::operator<(const Student &other) const {
    return this->id < other.getId();
}
/** @brief Checks if a student id is greater than another
 * @details Time complexity: O(1)
 * @param other Student to compare
 * @return true if it is greater than, false otherwise
 */
bool Student::operator>(const Student &other) const {
    return this->id > other.getId();
}