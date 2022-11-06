#ifndef TRABALHO_SCHEDULEMANAGER_H
#define TRABALHO_SCHEDULEMANAGER_H

#include <queue>
#include <set>
#include "Student.h"
#include "ClassSchedule.h"
#include "Request.h"

/**
 * @brief Class to store the information about the schedules, changingRequests and students.
 */

class ScheduleManager {
    public:
        ScheduleManager();

        void readFiles();
        void createSchedules();
        void setSchedules();
        void createStudents();

        unsigned long binarySearchSchedules(const UcClass &desiredUcCLass) const;
        Student* findStudent(const string &studentId) const;
        ClassSchedule* findSchedule(const UcClass &ucClass) const;
        vector<ClassSchedule> classesOfUc(const string &ucId) const;
        vector<Student> studentsOfUc(const string &ucId) const;
        int getNumberOfStudentsUc(const string &ucId) const;
        int getNumberOfStudentsUcClass(const UcClass &ucClass) const;
        int getNumberOfPendingRequests() const;
        UcClass getFormerClass(const Request &request) const;

        void addChangingRequest(const Student &student, const UcClass &ucClass);
        void addEnrollmentRequest(const Student &student, const UcClass &ucClass);
        void addRemovalRequest(const Student &student, const UcClass &ucClass);
        bool classesOverlap(const UcClass &c1, const UcClass &c2) const;
        bool requestHasCollision(const Request &request) const;
        bool requestExceedsCap(const Request &request) const;
        bool requestProvokesDisequilibrium(const Request &request) const;
        void processChangingRequest(const Request &request);
        void processRemovalRequest(const Request &request);
        void processEnrollmentRequest(const Request &request);
        void processRequests();
        void writeFiles() const;
        void printPendingRequests() const;
        void printRejectedRequests() const;

        void printStudentSchedule(const string &studentId) const;
        void printClassSchedule(const string &classCode) const;
        void printUcSchedule(const string &ucId) const;
        void printClassStudents(const UcClass &ucClass, const string &orderType) const;
        void printUcStudents(const string &ucId,  const string &sortType) const;

    private:
        /** @brief Set that stores all the students */
        set<Student> students;
        /** @brief Vector that stores all the schedules */
        vector<ClassSchedule> schedules;
        /** @brief Queue that stores all the changing requests */
        queue<Request> changingRequests;
        /** @brief Queue that stores all the removal requests */
        queue<Request> removalRequests;
        /** @brief Queue that stores all the enrollment requests */
        queue<Request> enrollmentRequests;
        /** @brief Queue that stores all the rejected changingRequests */
        vector<pair<Request, string>> rejectedRequests;
};


#endif //TRABALHO_SCHEDULEMANAGER_H
