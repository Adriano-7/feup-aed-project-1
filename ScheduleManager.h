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
        int binarySearchSchedules(UcClass desiredUcCLass) const;
        bool requestHasCollision(Request request);
        bool classesCollide(UcClass c1, UcClass c2);
        void printStudentSchedule(string studentId);
        void addRequest(Student &student, UcClass &ucClass);
        Student findStudent(string studentId) const;
        bool studentExists(string studentId) const;
        bool ucClassExists(string ucId, string classId) const;

    private:
        set <Student> students;
        vector<ClassSchedule> schedules;
        queue<Request> requests;
};


#endif //TRABALHO_SCHEDULEMANAGER_H
