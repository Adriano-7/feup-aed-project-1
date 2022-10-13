#include "Lesson.h"
#include <string>


using namespace std;

Lesson::Lesson(string class_no, string UCCode, string weekday, float beginTime, float duration, string type) {
    this->UCCode = UCCode;
    this->weekday = weekday;
    this->beginTime = beginTime;
    this->duration = duration;
    this->type = type;
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

bool Lesson::operator<(const Lesson lesson)  {
    return this->beginTime > lesson.beginTime;
}

bool Lesson::operator==(Lesson lesson) {
    return UCCode == lesson.UCCode;
}

