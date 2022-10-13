#include "Schedule.h"



using namespace std;

Schedule::Schedule() {
}
vector<Lesson> Schedule::getLessons() const {
    return lessons;
}
void Schedule::setLessons(vector<Lesson> lessons) {
    this->lessons = lessons;
}
void Schedule::addLesson(Lesson lesson) {
    lessons.push_back(lesson);
}
void Schedule::removeLesson(Lesson lesson) {
    lessons.erase(find(lessons.begin(),lessons.end(),lesson));
}

