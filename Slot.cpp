#include "Slot.h"
#include <string>
#include <map>

using namespace std;

Slot::Slot(){
    weekDay = "";
    startTime = 0;
    endTime = 0;
    type = "";
}

/**
 * @brief Class constructor that sets weekDay, startTime, endtime(startTime+duration) and type
 * @details Time complexity: O(1)
 */
Slot::Slot(const string &weekDay, const float &startTime, const float &duration, const string &type) {
    this->weekDay = weekDay;
    this->startTime = startTime;
    this->endTime = startTime + duration;
    this->type = type;
}

/** @brief Returns the weekDay of the slot
 * @details Time complexity: O(1)
 * @return weekDay
 */
string Slot::getWeekDay() const {
    return weekDay;
}

/** @brief Returns the type(T, P, PL) of the slot
 * @details Time complexity: O(1)
 * @return type
 */
string Slot::getType() const {
    return type;
}

/** @brief Returns the startTime of the slot
 * @details Time complexity: O(1)
 * @return startTime
 */
float Slot::getStartTime() const {
    return startTime;
}

/** @brief Returns the endTime of the slot
 * @details Time complexity: O(1)
 * @return endTime
 */
float Slot::getEndTime() const {
    return endTime;
}

/** @brief Checks if two slots overlap
 * @details Two slots overlap if they have the same weekDay and if they have overlapping time intervals. Slots of type 'T' can always overlap with other slots.\n
 * Time complexity: O(1)
 * @param slot Slot to compare
 * @return true if there is a conflict, false otherwise
 */
bool Slot::overlaps(const Slot &other) const {
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
    return this->weekDay != other.getWeekDay() && this->startTime != other.getStartTime() && this->endTime != other.getEndTime() && this->type != other.getType();
}

/** @brief Checks if two slots are equal, when they have the same weekday, start time, end time and type
 * @details Time complexity: O(1)
 * @param other Slot to compare
 * @return true if they are equal, false otherwise
 */
bool Slot::operator==(const Slot &other) const {
    return this->weekDay==other.getWeekDay() && this->startTime == other.getStartTime() && this->endTime == other.getEndTime() && this->type == other.getType();
}

/** @brief Checks if a slot is less than another
 * @details A slot is smaller than another if it happens earlier in the week\n
 * Time complexity: O(1)
 * @param other Slot to compare
 * @return true if it is less than the other, false otherwise
 */
bool Slot::operator<(const Slot &other) const {
    if(this->weekDay != other.getWeekDay()) {
        map <string, int> days = {{"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}, {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}, {"Sunday", 7}};
        return days[weekDay] < days[other.getWeekDay()];
    }

    if(this->startTime == other.getStartTime()){
        if(this->endTime == other.getEndTime()){
            return this->type < other.getType();
        }
        return this->endTime < other.getEndTime();
    }
    return this->startTime < other.getStartTime();
}