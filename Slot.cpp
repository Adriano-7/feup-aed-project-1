#include "Slot.h"
#include <string>

using namespace std;

/**
 * @brief Class constructor that sets weekDay, startTime, endtime(startTime+duration) and type.
 * @details Time complexity: O(1)
 */
Slot::Slot(const string &weekDay, const float &startTime, const float &duration, const string &type) {
    this->weekDay = weekDay;
    this->startTime = startTime;
    this->endTime = startTime + duration;
    this->type = type;
}
/** @brief Getter of the weekDay
 * @details Time complexity: O(1)
 * @return weekDay
 */
string Slot::getWeekDay() const {
    return weekDay;
}

/** @brief Getter of the class time
 * @details Time complexity: O(1)
 * @return type
 */
string Slot::getType() const {
    return type;
}

/** @brief Getter of the startTime
 * @details Time complexity: O(1)
 * @return startTime
 */
float Slot::getStartTime() const {
    return startTime;
}

/** @brief Getter of the endTime
 * @details Time complexity: O(1)
 * @return endTime
 */
float Slot::getEndTime() const {
    return endTime;
}
/** @brief Checks if there is a conflict between two slots
 * @details Time complexity: O(1)
 * @param slot Slot to compare
 * @return true if there is a conflict, false otherwise
 */
bool Slot::collides(const Slot &other) const {
    if (this->weekDay != other.getWeekDay()) {

        return false;
    }
    if (this->startTime >= other.getEndTime() || this->endTime <= other.getStartTime()) {
        return false;
    }
    if(this->type == "T" || other.getType() == "T") {
        return false;
    }
    return true;
}
/** @brief Checks if two slots are different
 * @details Time complexity: O(1)
 * @param other Slot to compare
 * @return true if they are different, false otherwise
 */
bool Slot::operator!=(const Slot &other) const {
    return this->startTime != other.getStartTime() && this->endTime != other.getEndTime() && this->type != "T" && other.getType() != "T";
}
/** @brief Checks if two slots are equal, when they have the same start time, end time and type
 * @details Time complexity: O(1)
 * @param other Slot to compare
 * @return true if they are equal, false otherwise
 */
bool Slot::operator==(const Slot &other) const {
    return this->startTime == other.getStartTime() && this->endTime == other.getEndTime() && this->type == other.getType();
}