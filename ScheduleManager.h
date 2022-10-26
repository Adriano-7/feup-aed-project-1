#ifndef TRABALHO_SCHEDULEMANAGER_H
#define TRABALHO_SCHEDULEMANAGER_H

#include <queue>
#include <set>
#include "Student.h"
#include "ClassSchedule.h"
#include "Request.h"


class ScheduleManager {
    public:
        ScheduleManager();
        void readFiles();
        void createSchedules();
        void setSchedules();
        void printSchedules() const;
        void createStudents();
        int BSearchSchedules(UcClass desiredUcCLass);
        set<Student> BSTfromStudents();

    private:

        vector<Student> students;
        vector<ClassSchedule> schedules;
        queue<Request> requests;
};


#endif //TRABALHO_SCHEDULEMANAGER_H
