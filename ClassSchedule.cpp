#include "ClassSchedule.h"
#include <iostream>
#include <algorithm>

using namespace std;

/**@brief Default Constructor, initialized with an empty vector of slots and students
 * @details Time complexity: O(1)
 */
ClassSchedule::ClassSchedule() {
    this->ucClass = UcClass();
    this->slots = vector<Slot>();
}

/**@brief Constructor, sets ucClass to the given one. The vector of slots is set to empty
* @details Time complexity: O(1)
* @param UcClass the UcClass of the schedule
*/
ClassSchedule::ClassSchedule(const UcClass &ucClass) {
    this->ucClass = ucClass;
    this->slots = vector<Slot>();
}

/**@brief Constructor, given a ucId and a classId, creates a ClassSchedule with the the vector of slots empty
 * @details Time complexity: O(1)
 * @param ucId
 * @param classId
 */
ClassSchedule::ClassSchedule(const string &ucId, const string &classId) {
    this->ucClass = UcClass(ucId, classId);
    this->slots = vector<Slot>();
}

/** @brief Add a slot to the vector of slots
 * @details Time complexity: O(1)
 * @param slot the slot to be added
*/
void ClassSchedule::addSlot(const Slot &slot) {
    slots.push_back(slot);
}

/** @brief Add a student to the set of students
 * @details Time complexity: O(log n)
 * @param student the student to add
 */
void ClassSchedule::addStudent(const Student &student) {
    students.insert(student);
}

/** @brief Remove a student from the set of students
 * @details Time complexity: O(log n)
 * @param student the student to remove
 */
void ClassSchedule::removeStudent(const Student &student) {
    students.erase(student);
}

/** @brief Bolean function that returns true if both ClassSchedule have the same UcId, false otherwise
 * @details Time complexity: O(1)
 * @param other the other ClassSchedule
 */
bool ClassSchedule::sameUC(const ClassSchedule &other) const {
    return ucClass.sameUC(other.getUcClass());
}

/**@brief Prints the ucId and classId
 * @details Time complexity: O(1)
 */
void ClassSchedule::printHeader() const {
    cout << ">> UC:" << ucClass.getUcId() << " " << ucClass.getClassId() << endl;
}

/**@brief Prints each slot (Weekday, Start time, End time, Type)
 * @details Time complexity: O(n)
 */
void ClassSchedule::printSlots() const {
    cout << ">> Slots:" << endl;
    for (const auto &slot : slots) {
        cout << "   " << slot.getWeekDay() << "   " << slot.getStartTime() << " - " << slot.getEndTime() << "   " << slot.getType() << endl;
    }
}

/**@brief Prints the students in a given sortType
 * @details Time complexity: O(n log n)
 * @param sortType the type of sort, it can be alphabetical, reverse alphabetical, numerical, reverse numerical
 */
void ClassSchedule::printStudents(const string &sortType) const{
    auto studentsVector = new vector<Student>(students.begin(), students.end());            //O(n)
    if (sortType == "alphabetical") {
        sort(studentsVector->begin(), studentsVector->end(), [](const Student &a, const Student &b) { return a.getName() < b.getName(); }); //O(n logN)
    } else if (sortType == "reverse alphabetical") {
        sort(studentsVector->rbegin(), studentsVector->rend(), [](const Student &a, const Student &b) { return a.getName() < b.getName(); }); //O(n logN)
    } else if (sortType == "numerical") {
        sort(studentsVector->begin(), studentsVector->end());   //O(n logN)
    } else if (sortType == "reverse numerical") {
        sort(studentsVector->rbegin(), studentsVector->rend()); //O(n logN)
    } else {
        cout << "Invalid sortType" << endl;
        return;
    }
    cout << ">> Number of students: " << students.size() << endl;
    cout << ">> Students:" << endl;
    for(const Student &student: *studentsVector){   //O(n)
        cout << "   "; student.printHeader();
    }
    delete studentsVector;
}

/**@brief Prints the ClassSchedule(calls printHeader, printSlots and printStudents)
 * @details Time complexity: O(n log n)
*/
void ClassSchedule::print() const {
    printHeader();  //O(1)
    printSlots();   //O(n)
    printStudents();    //O(n log n)
    cout << endl;
}

/**@brief Get the UcClass
 * @details Time complexity: O(1)
*/
UcClass ClassSchedule::getUcClass() const {
    return ucClass;
}

/** @brief Get the number of students in the class
 * @details Time complexity: O(1)
 * @return the number of students
 */
int ClassSchedule::getNumStudents() const {
    return students.size();
}

/**
 * @brief Get the slots
 * @details Time complexity: O(1)
 * @return the reference to the vector of slots
*/
const vector<Slot> &ClassSchedule::getSlots() const {
    return slots;
}

/**@brief Get students
 * @details Time complexity: O(1)
*/
set<Student> ClassSchedule::getStudents() const {
    return students;
}

/** @brief Minor operator
 * @details Time complexity: O(1)
 * @param other The ClassSchedule to compare to
 * @return true if the UcClass is smaller, false otherwise
 */
bool ClassSchedule::operator < (const ClassSchedule &other) const {
    return this->ucClass < other.getUcClass();
}

/** @brief Equality operator
 * @details Time complexity: O(1)
 * @param other The ClassSchedule to compare to
 * @return true if the UcClass is equal, false otherwise
 */
bool ClassSchedule::operator == (const ClassSchedule &other) const {
    return this->ucClass == other.getUcClass();
}