#include "Schedule.h"
#include <set>
#include "Lesson.h"

using namespace std;

Schedule::Schedule() {
}
set<Lesson> Schedule::getLessons() const {
    return lessons;
}
void Schedule::setLessons(set<Lesson> lessons) {
    this->lessons = lessons;
}
void Schedule::addLesson(Lesson lesson) {
    lessons.insert(lesson);
}
void Schedule::removeLesson(Lesson lesson) {
    lessons.erase(lesson);
}

