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

float Slot::getDuration() const {
    return endTime - beginTime;
}