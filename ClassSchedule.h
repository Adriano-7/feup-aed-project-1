#ifndef TRABALHO_CLASSSCHEDULE_H
#define TRABALHO_CLASSSCHEDULE_H

#include <vector>
#include <set>
#include "Slot.h"
#include "UcClass.h"
#include "Student.h"

/**
 * @brief Class that represents a schedule for a class in a given Course, with a vector of slots and a set of students
 */
class ClassSchedule {
    public:
        ClassSchedule();
        ClassSchedule(const UcClass &ucClass);
        ClassSchedule(const string &ucId, const string &classId);

        void addSlot(const Slot &slot);
        void addStudent(const Student &student);
        void removeStudent(const Student &student);
        bool sameUC(const ClassSchedule &other) const;

        void printHeader() const;
        void printSlots() const;
        void printStudents(const string &sortType = "alphabetical") const;
        void print() const;

        UcClass getUcClass() const;
        int getNumStudents() const;
        const vector<Slot> &getSlots() const;
        set<Student> getStudents() const;
        bool operator < (const ClassSchedule &other) const;
        bool operator == (const ClassSchedule &other) const;

    private:
        /** @brief Information about the class and UC that the schedule is for */
        UcClass ucClass;
        /** @brief Vector of slots that constitutes the schedule */
        vector<Slot> slots;
        /** @brief Set of students that are enrolled in the class in this UC */
        set<Student> students;
};

#endif //TRABALHO_CLASSSCHEDULE_H
