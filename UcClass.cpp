#include "UcClass.h"

/** @brief Standard constructor of the UcClass class
 * @details Time complexity: O(1)
 */
UcClass::UcClass() {
    this->ucId = "";
    this->classId = "";
}

/**
 * @brief Constructor of the UcClass class
 * @details Time complexity: O(1)
 * @param ucId Id of the UC
 * @param classId Id of the class
 * @param capacity Capacity of the class
 * @param enrolled Number of students enrolled in the class
 */
UcClass::UcClass(const string &ucId, const string &classId) {
    this->ucId = ucId;
    this->classId = classId;
}

/**
 * @brief Checks if two classes have the same UC
 * @details Time complexity: O(1)
 * @param other Class to compare
 * @return true if they have the same UC, false otherwise
 */
bool UcClass::sameUC(const UcClass &other) const {
    return this->ucId == other.ucId;
}

/**
 * @brief Getter of the UC id
 * @details Time complexity: O(1)
 * @return ucId
 */
string UcClass::getUcId() const {
    return ucId;
}
/**
 * @brief Getter of the class id
 * @details Time complexity: O(1)
 * @return classId
 */
string UcClass::getClassId() const {
    return classId;
}

/**
 * @brief Checks if two classes are equal
 * @details Time complexity: O(1)
 * @param other Class to compare
 * @return true if they are equal, false otherwise
 */
bool UcClass::operator == (const UcClass &other) const {
    return this->ucId == other.ucId && this->classId == other.classId;
}
/**
 * @brief Checks if a class ID is less than another
 * @details Time complexity: O(1)
 * @param other Class to compare
 * @return true if it is less than, false otherwise
 */
bool UcClass::operator < (const UcClass &other) const {
    if(this->ucId == other.ucId) return this->classId < other.classId;
    return this->ucId < other.ucId;
}
/**
 * @brief Checks if a class ID is greater than another
 * @details Time complexity: O(1)
 * @param other Class to compare
 * @return true if it is greater than, false otherwise
 */
bool UcClass::operator > (const UcClass &other) const {
    if(this->ucId == other.ucId) return this->classId > other.classId;
    return this->ucId > other.ucId;
}
