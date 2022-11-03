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
        /**Default Constructor, initialized with an empty vector of slots and students*/
        ClassSchedule();

        /**Constructor, sets ucClass to the given one. The vector of slots is set to empty.
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

        /**Prints the students in a given sortType
         * @param sortType the type of sort, it can be alphabetical, reverse alphabetical, numerical, reverse numerical
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

        /** Add a slot to the vector of slots
         * @param slot the slot to be added
        */
        void addSlot(const Slot &slot);

        /**
         * Get the slots
         * @return the reference to the vector of slots
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

        /**Bolean function that returns true if both ClassSchedule have the same UcId, false otherwise
         * @param other the other ClassSchedule
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
        /** @brief Information about the class and UC that the schedule is for */
        UcClass ucClass;
        /** @brief Vector of slots that constitutes the schedule */
        vector<Slot> slots;
        /** @brief Set of students that are enrolled in the class in this UC */
        set<Student> students;
};

#endif //TRABALHO_CLASSSCHEDULE_H
