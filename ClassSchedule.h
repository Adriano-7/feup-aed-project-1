#ifndef TRABALHO_CLASSSCHEDULE_H
#define TRABALHO_CLASSSCHEDULE_H

#include <vector>
#include <set>
#include "Slot.h"
#include "UcClass.h"
#include "Student.h"

/**
 * @brief Class that represents a schedule for a class
 * @details
 */

class ClassSchedule {
    public:
        /**Default Constructor, ucClass default constructor is called and vector of slots is set to empty*/
        ClassSchedule();

        /**Constructor, the vector of slots is set to empty
        * @param UcClass the UcClass of the schedule
        */
        ClassSchedule(const UcClass &ucClass);

        /**Constructor, given a ucId and a classId, creates a ClassSchedule with the the vector of slots empty
         *
         * @param ucId
         * @param classId
         */
        ClassSchedule(const string &ucId, const string &classId);

        /**Prints the ucId and classId
         */
        void printHeader() const;

        /**Prints each slot (Weekday, Start time, End time, Type)
         */
        void printSlots() const;

        /**Prints the students in a given sortType: alphabetical, reverse alphabetical, numerical, reverse numerical
         */
        void printStudents(const string &sortType = "alphabetical") const;

        /**Prints the ClassSchedule(calls printHeader, printSlots and printStudents)
        */
        void print() const;

        /**Get the UcClass
        */
        UcClass getUcClass() const;

        /**Get students
        */
        set<Student> getStudents() const;

        /**Get add the slot to the vector of slots
        */
        void addSlot(const Slot &slot);

        /**
         * @return vector of slots
        */
        const vector<Slot> &getSlots() const;

        /** Get the number of students in the class
         * @return the number of students
         */
        int getNumStudents() const;

        /** Add a student to the set of students
         * @param student the student to add
         */
        void addStudent(const Student &student);

        /** Remove a student from the set of students
         * @param student the student to remove
         */
        void removeStudent(const Student &student);

        /**Bolean function that returns true if both ClassSchedule have the same UcId, false otherwise
         */
        bool sameUC(ClassSchedule other) const;

        /** Minor operator
         * @param other The ClassSchedule to compare to
         * @return true if the UcClass is smaller, false otherwise
         */
        bool operator < (const ClassSchedule &other) const;

        /** Equality operator
         * @param other The ClassSchedule to compare to
         * @return true if the UcClass is equal, false otherwise
         */
        bool operator == (const ClassSchedule &other) const;

    private:
        UcClass ucClass;
        vector<Slot> slots;
        set<Student> students;
};

#endif //TRABALHO_CLASSSCHEDULE_H
