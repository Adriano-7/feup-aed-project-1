#ifndef TRABALHO_SCHEDULEMANAGER_H
#define TRABALHO_SCHEDULEMANAGER_H

#include <queue>
#include <set>
#include "Student.h"
#include "ClassSchedule.h"
#include "Request.h"

/**
 * @brief Class that represents the schedule manager
 * @details This is the class reponsabile for managing the schedules
 */
class ScheduleManager {
    public:
        ScheduleManager();
        void readFiles();
        void createSchedules();
        void setSchedules();
        void createStudents();

        unsigned long binarySearchSchedules(const UcClass &desiredUcCLass) const;
        bool requestHasCollision(const Request &request) const;
        bool requestExceedsMaxStudents(const Request &request) const;
        bool classesCollide(const UcClass &c1, const UcClass &c2) const;
        void addRequest(const Student &student, const UcClass &ucClass);
        void addRequest(const Request &request);
        bool acceptRequest(const Request &request) const;
        void processRequest(const Request &request);
        void processRequests();

        void printStudentSchedule(const string &studentId) const;
        void printClassSchedule(const string &classCode) const;
        void printUcStudents(const string &ucId) const;
        void printUcSchedule(const string &ucId) const;
        void printPendingRequests() const;
        void printRejectedRequests() const;

        Student* findStudent(const string &studentId) const;
        ClassSchedule* findSchedule(const UcClass &ucClass) const;
        vector<ClassSchedule> classesOfSubject(const string &ucId) const;
        vector<Student> studentsOfSubject(const string &ucId) const;

        const vector<ClassSchedule> &getSchedules() const;
        const set<Student> &getStudents() const;

    private:
        set<Student> students;
        vector<ClassSchedule> schedules;
        queue<Request> requests;
        vector<Request> rejectedRequests;
};


#endif //TRABALHO_SCHEDULEMANAGER_H
