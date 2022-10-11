#include "Lesson.h"
#include <string>
#include "Class.h"

using namespace std;

Lesson::Lesson(string UCCode, string weekday, float beginTime, float duration, string type, Class _class) {
    this->UCCode = UCCode;
    this->weekday = weekday;
    this->beginTime = beginTime;
    this->duration = duration;
    this->type = type;
    this->_class = _class;
}

string Lesson::getUCCode() const {
    return UCCode;
}

string Lesson::getWeekday() const {
    return weekday;
}

float Lesson::getBeginTime() const {
    return beginTime;
}

float Lesson::getDuration() const {
    return duration;
}

string Lesson::getType() const {
    return type;
}

Class Lesson::getClass() const {
    return _class;
}

void Lesson::setUCCode(string UCCode) {
    this->UCCode = UCCode;
}

void Lesson::setWeekday(string weekday) {
    this->weekday = weekday;
}

void Lesson::setBeginTime(float beginTime) {
    this->beginTime = beginTime;
}

void Lesson::setDuration(float duration) {
    this->duration = duration;
}

void Lesson::setType(string type) {
    this->type = type;
}

void Lesson::setClass(Class _class) {
    this->_class = _class;
}