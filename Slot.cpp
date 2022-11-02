#include "Slot.h"
#include <string>

using namespace std;


Slot::Slot(const string &weekDay, const float &startTime, const float &duration, const string &type) {
    this->weekDay = weekDay;
    this->startTime = startTime;
    this->endTime = startTime + duration;
    this->type = type;
}

string Slot::getWeekDay() const {
    return weekDay;
}

float Slot::getStartTime() const {
    return startTime;
}

string Slot::getType() const {
    return type;
}

float Slot::getEndTime() const {
    return endTime;
}


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

bool Slot::operator!=(const Slot &other) const {
    return this->startTime != other.getStartTime() && this->endTime != other.getEndTime() && this->type != "T" && other.getType() != "T";
}

bool Slot::operator==(const Slot &other) const {
    return this->startTime == other.getStartTime() && this->endTime == other.getEndTime() && this->type == other.getType();
}