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
        void createStudents();

        int binarySearchSchedules(const UcClass &desiredUcCLass) const;
        bool requestHasCollision(const Request &request) const;
        bool classesCollide(const UcClass &c1, const UcClass &c2) const;
        void printStudentSchedule(const string &studentId) const;
        void printClassSchedule(const string &classCode) const;
        void addRequest(const Student &student, const UcClass &ucClass);
        void addRequest(const Request &request);
        Student* findStudent(const string &studentId) const;
        ClassSchedule* findSchedule(const UcClass &ucClass) const;

        const vector<ClassSchedule> &getSchedules() const;
        const set<Student> &getStudents() const;

    private:
        set <Student> students;
        vector<ClassSchedule> schedules;
        queue<Request> requests;
};


#endif //TRABALHO_SCHEDULEMANAGER_H
