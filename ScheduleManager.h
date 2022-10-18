#ifndef TRABALHO_SCHEDULEMANAGER_H
#define TRABALHO_SCHEDULEMANAGER_H

#include <queue>
#include "Student.h"
#include "ClassSchedule.h"
#include "Request.h"

class ScheduleManager {
    public:
        void create_schedules();
        void readFiles();

    private:
        set<Student> students;
        vector<ClassSchedule> schedules;
        queue<Request> requests;
};


#endif //TRABALHO_SCHEDULEMANAGER_H
