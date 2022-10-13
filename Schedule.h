#ifndef TRABALHO_SCHEDULE_H
#define TRABALHO_SCHEDULE_H

#include <vector>
#include "Lesson.h"
#include<bits/stdc++.h>

using namespace std;

class Schedule {
    public:
        Schedule();
        vector<Lesson> getLessons() const;
        void setLessons(vector<Lesson> lessons);
        void addLesson(Lesson lesson);
        void removeLesson(Lesson lesson);

    private:
        vector<Lesson> lessons;
};


#endif //TRABALHO_SCHEDULE_H
