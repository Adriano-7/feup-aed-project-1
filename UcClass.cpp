#include <map>
#include "UcClass.h"

/** @brief Standard constructor of the UcClass class. ucId and classId are set to empty strings
 * @details Time complexity: O(1)
 */
UcClass::UcClass() {
    this->ucId = "";
    this->classId = "";
}

/**
 * @brief Constructor of the UcClass class. ucId and classId are set to the given values
 * @details Time complexity: O(1)
 * @param ucId Id of the UC
 * @param classId Id of the class
 */
UcClass::UcClass(const string &ucId, const string &classId) {
    this->ucId = ucId;
    this->classId = classId;
}

/**
 * @brief Checks if two classes have the same UcId
 * @details Time complexity: O(1)
 * @param other Class to compare
 * @return true if they have the same UcId, false otherwise
 */
bool UcClass::sameUcId(const UcClass &other) const {
    return this->ucId == other.ucId;
}

/**
 * @brief Returns the UcId of the class
 * @details Time complexity: O(1)
 * @return The UcId of the UcClass
 */
string UcClass::getUcId() const {
    return ucId;
}
/**
 * @brief Returns the classId of the class
 * @details Time complexity: O(1)
 * @return classId
 */
string UcClass::getClassId() const {
    return classId;
}

/**
 * @brief Checks if two UcClasses have the same UcId and classId
 * @details Time complexity: O(1)
 * @param other Class to compare
 * @return true if they have the same UcId and ClassId, false otherwise
 */
bool UcClass::operator == (const UcClass &other) const {
    return this->ucId == other.ucId && this->classId == other.classId;
}
/**
 * @brief Checks if a UcId is less than another. If they have the same UcId, it compares the ClassId.
 * @details Time complexity: O(1)
 * @param other Class to compare
 * @return true if it is less than, false otherwise
 */
bool UcClass::operator < (const UcClass &other) const {
    if(this->ucId == other.ucId) return this->classId < other.classId;
    return this->ucId < other.ucId;
}
/**
 * @brief Checks if a UcId is greater than another. If they have the same UcId, it compares the ClassId.
 * @details Time complexity: O(1)
 * @param other Class to compare
 * @return true if it is greater than, false otherwise
 */
bool UcClass::operator > (const UcClass &other) const {
    if(this->ucId == other.ucId) return this->classId > other.classId;
    return this->ucId > other.ucId;
}
