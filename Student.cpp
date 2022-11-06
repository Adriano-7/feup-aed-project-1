#include "Student.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
/**
 * @brief Constructor that sets the id, name of the student to be an empty string. Vector of classes is empty
 * @details Time complexity: O(1)
 */
Student::Student() {
    this->id = "";
    this->name = "";
    this->classes = vector<UcClass>();
}
/**
 * @brief Class constructor that receives the id and name of the student. Vector of classes is empty
 * @details Time complexity: O(1)
 */
Student::Student(const string &id, const string &name) {
    this->id = id;
    this->name = name;
    this->classes = vector<UcClass>();
}
/** @brief Adds a class to the student.
 *  @details Time complexity: O(1)
 */
void Student::addClass(const UcClass &newClass) {
    classes.push_back(newClass);
}
/** @brief Changes a class of the student. If the student was not enrolled in the class, nothing changes and it returns an empty UcClass
 *  @details Time complexity: O(h) where h is the number of classes the student is enrolled
 *  @return The oldClass if the student was enrolled in the uc, an empty UcClass otherwise.
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

/** @brief Removes a uc from the student classes.
 *  @details Time complexity: O(h) where h is the number of classes the student is currently enrolled in
 */
void Student::removeUc(const string &ucCode) {
    for (int i = 0; i < classes.size(); i++) {
        if (classes.at(i).getUcId() == ucCode) {
            classes.erase(classes.begin() + i);
            return;
        }
    }
}

/** @brief Adds a ucClass to the student. And then sorts the vector of classes
 *  @details Time complexity: O(hlog h) where h is the number of classes the student is currently enrolled in
 */
void Student::addUc(const UcClass &newClass) {
    classes.push_back(newClass); // O(1)
    sort(classes.begin(), classes.end());
}

/** @brief Checks if the student is enrolled in a given UC
 * @details Time complexity: O(h) where h is the number of classes the student is currently enrolled in
 * @param ucCode UcCode to check
 * @return true if the student is enrolled, false otherwise
 */
bool Student::isEnrolled(const string &ucCode) const {
    for (const UcClass &i : classes) {
        if (i.getUcId() == ucCode) {
            return true;
        }
    }
    return false;
}

/** @brief Given a Uc finds the pair UcClass of the student
 * @details Time complexity: O(h) where h is the number of classes of the student
 * @param ucCode UC code to check
 * @return The UcClass of the student if the student is enrolled in the UC, an empty UcClass otherwise
 */
UcClass Student::findUcClass(const string &ucCode) const {
    for (const UcClass &i : classes) {
        if (i.getUcId() == ucCode) {
            return i;
        }
    }
    return {};
}

/** @brief Prints the header of the student (Name and ID)
 * @details Time complexity: O(1)
 */
void Student::printHeader() const {
    cout << name << " - " << id << endl;
}

/** @brief Prints the classes of the student
 * @details Time complexity: O(h) where h is the number of classes the student is currently enrolled in
 */
void Student::printClasses() const {
    int i = 0;
    while(i < classes.size()-1){
        cout << classes[i].getUcId() << " " << classes[i].getClassId() << "  |  ";
        i++;
    }
    cout << classes[i].getUcId() << " " << classes[i].getClassId() << endl;
}

/** @brief Prints the name of the student and the classes he's enrolled in (calls printHeader and printClasses)
 * @details Time complexity: O(h) where h is the number of classes the student is currently enrolled in
 */
void Student::print() const {
    cout << "Student: "; printHeader();
    cout << "Classes: "; printClasses();
}

/** @brief Returns the id of the student
 * @details Time complexity: O(1)
 * @return The id of the student
 */
string Student::getId() const {
    return id;
}
/** @brief Returns the name of the student
 * @details Time complexity: O(1)
 * @return The name of the student
 */
string Student::getName() const {
    return name;
}
/** @brief Returns the vector of classes of the student
 * @details Time complexity: O(1)
 * @return classes
 */
vector <UcClass> Student::getClasses() const {
    return classes;
}

/** @brief Checks if two students have the same ID
 * @details Time complexity: O(1)
 * @param other Student to compare
 * @return true if they have the same id, false otherwise
 */
bool Student::operator==(const Student &other) const{
    return this->id == other.getId();
}
/** @brief Checks if the student has a smaller ID than the other student
 * @details Time complexity: O(1)
 * @param other Student to compare
 * @return true if it is less than, false otherwise
 */
bool Student::operator<(const Student &other) const {
    return this->id < other.getId();
}
/** @brief Checks if the student has a bigger ID than the other student
 * @details Time complexity: O(1)
 * @param other Student to compare
 * @return true if it is greater than, false otherwise
 */
bool Student::operator>(const Student &other) const {
    return this->id > other.getId();
}