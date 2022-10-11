#ifndef TRABALHO_SCHEDULE_H
#define TRABALHO_SCHEDULE_H

#include <set>
#include "Lesson.h"

using namespace std;

class Schedule {
    public:
        Schedule();
        set<Lesson> getLessons() const;
        void setLessons(set<Lesson> lessons);
        void addLesson(Lesson lesson);
        void removeLesson(Lesson lesson);
    private:
        set<Lesson> lessons;
};


#endif //TRABALHO_SCHEDULE_H
