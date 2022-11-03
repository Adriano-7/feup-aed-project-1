#ifndef TRABALHO_SCHEDULEMANAGER_H
#define TRABALHO_SCHEDULEMANAGER_H

#include <queue>
#include <set>
#include "Student.h"
#include "ClassSchedule.h"
#include "Request.h"

/**
 * @brief Class to store the information about the schedules, requests and students.
 */

class ScheduleManager {
    public:
        ScheduleManager();

        void readFiles();
        void createSchedules();
        void setSchedules();
        void createStudents();

        unsigned long binarySearchSchedules(const UcClass &desiredUcCLass) const;
        bool classesCollide(const UcClass &c1, const UcClass &c2) const;
        bool requestHasCollision(const Request &request) const;
        Student* findStudent(const string &studentId) const;
        ClassSchedule* findSchedule(const UcClass &ucClass) const;
        vector<ClassSchedule> classesOfSubject(const string &ucId) const;
        vector<Student> studentsOfSubject(const string &ucId) const;
        void addRequest(const Student &student, const UcClass &ucClass);
        bool requestExceedsMaxStudents(const Request &request) const;
        bool acceptRequest(const Request &request) const;
        void processRequest(const Request &request);
        void processRequests();
        void writeFiles() const;

        void printStudentSchedule(const string &studentId) const;
        void printClassSchedule(const string &classCode) const;
        void printUcSchedule(const string &ucId) const;
        void printUcStudents(const string &ucId) const;
        void printPendingRequests() const;
        void printRejectedRequests() const;

    private:
        /** @brief Set that stores all the students */
        set<Student> students;
        /** @brief Vector that stores all the schedules */
        vector<ClassSchedule> schedules;
        /** @brief Queue that stores all the requests */
        queue<Request> requests;
        /** @brief Queue that stores all the rejected requests */
        vector<Request> rejectedRequests;
};


#endif //TRABALHO_SCHEDULEMANAGER_H
