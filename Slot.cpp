#include "Slot.h"
#include <string>
#include <iostream>


using namespace std;

Slot::Slot(string class_no, string UCCode, string weekday, float beginTime, float duration, string type) {
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

bool Slot::operator<(const Slot lesson)  {
    return this->beginTime > lesson.beginTime;
}

bool Slot::operator==(Slot lesson) {
    return UCCode == lesson.UCCode;
}

ostream& operator<<(ostream& out, const Slot& lesson) {
    out << "UCCode: " << lesson.UCCode << " Weekday: " << lesson.weekday << " BeginTime: " << lesson.beginTime << " Duration: " << lesson.duration << " Type: " << lesson.type << endl;
    return out;
}