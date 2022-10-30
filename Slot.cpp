#include "Slot.h"
#include <string>
#include <iostream>


using namespace std;

Slot::Slot(string weekday, float beginTime, float duration, string type) {
    this->weekday = weekday;
    this->startTime = beginTime;
    this->endTime = beginTime + duration;
    this->type = type;
}

string Slot::getWeekDay() const {
    return weekday;
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



bool Slot::collides(Slot other) const {
    if (this->weekday != other.getWeekDay()) {
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