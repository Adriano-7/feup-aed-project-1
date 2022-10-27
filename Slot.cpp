#include "Slot.h"
#include <string>
#include <iostream>


using namespace std;

Slot::Slot(string weekday, float beginTime, float duration, string type) {
    this->weekday = weekday;
    this->beginTime = beginTime;
    this->endTime = beginTime + duration;
    this->type = type;
}

string Slot::getWeekday() const {
    return weekday;
}

float Slot::getBeginTime() const {
    return beginTime;
}

string Slot::getType() const {
    return type;
}

float Slot::getEndTime() const {
    return endTime;
}

bool Slot::collides(Slot other) const {
    if (this->weekday != other.getWeekday()) {
        return false;
    }
    if (this->beginTime >= other.getEndTime() || this->endTime <= other.getBeginTime()) {
        return false;
    }
    if(this->type == "T" || other.getType() == "T") {
        return false;
    }
    return true;
}