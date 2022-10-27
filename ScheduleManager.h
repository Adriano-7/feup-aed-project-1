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
        const vector<ClassSchedule> &getSchedules() const;
        void createStudents();
        const set<Student> &getStudents() const;
        int binarySearchSchedules(UcClass desiredUcCLass);
        bool requestHasCollision(Request request);
        bool classesCollide(UcClass c1, UcClass c2);
        void addRequest(Request request);

    private:
        set <Student> students;
        vector<ClassSchedule> schedules;
        queue<Request> requests;
};


#endif //TRABALHO_SCHEDULEMANAGER_H
