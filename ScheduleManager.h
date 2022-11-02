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
        /**
        * @brief Schedule Manager constructor
         * @details Creates a Schedule Manager with an empty set of students, a empty vector of schedules and a empty queue of requests
        */
        ScheduleManager();

        /**
        * @brief Reads the files and creates the objects
        */
        void readFiles();

        /**
        * @brief Reads the file "classes_per_uc.csv" and creates a vector of schedules with only the uc code and the class code
        */
        void createSchedules();

        /**
        * @brief Reads the file "classes.csv" and adds the slots to the schedules created in the previous function
        * @see createSchedules()
        */
        void setSchedules();

        /**
        * @brief Reads the students_classes.csv file and creates the students set
        * @details The students are created with the student id, name and the classes they are enrolled in
        */
        void createStudents();

        /**
        * @brief Function that returns the index of the schedule with the ucClass passed as parameter
        * @param desiredUcCLass
        * @details Uses binary search to find the schedules
        * @return The index of the schedule with the ucClass passed as parameter
         * @see Slot::collides()
        */
        unsigned long binarySearchSchedules(const UcClass &desiredUcCLass) const;

        /**
        * @brief Function that verifies if a given request has a conflict with the schedule of a given student
        * @param request
        * @return true if the request has a conflict with the schedule of the student, false otherwise
        */
        bool requestHasCollision(const Request &request) const;

        /**
        * @brief Function that verifies if the schedule of two given classes have a conflict
        * @return true if the classes have a conflict, false otherwise
        */
        bool classesCollide(const UcClass &c1, const UcClass &c2) const;

        /**
         * @brief Function that prints the schedule of a given student
         * @param studentId
         */
        void printStudentSchedule(const string &studentId) const;

        /**
         * @brief Function that prints the schedule of a given class
         * @param classCode
         */
        void printClassSchedule(const string &classCode) const;

        /**
         * @brief Function that prints the students enrolled a given uc
         * @param ucId
         */
        void printUcStudents(const string &ucId) const;

        /**
         * @brief Function that given a student id and the ucClass he wants to change to, adds the request to the queue of requests
         */
        void addRequest(const Student &student, const UcClass &ucClass);

        /**
         * @brief Function that adds a request to the queue of requests
         * @param request to add
         */
        void addRequest(const Request &request);

        /**
         * @brief Function that print the schedule of a given subject
         * @param subjectCode
         */
        void printUcSchedule(const string &ucId) const;

        /**
        * @brief Function that returns the student with the ID passed as parameter
        * @param studentId
        */
        Student* findStudent(const string &studentId) const;

        /**
        * @brief Function that returns the schedule with the ucClass passed as parameter
        * @param ucClass
        */
        ClassSchedule* findSchedule(const UcClass &ucClass) const;

        /**
         * @brief Getter of the vector of ClassSchedules
         */
        const vector<ClassSchedule> &getSchedules() const;

        /**
         * @brief Getter of set of students
         */
        const set<Student> &getStudents() const;

    private:
        set <Student> students;
        vector<ClassSchedule> schedules;
        queue<Request> requests;
};


#endif //TRABALHO_SCHEDULEMANAGER_H
