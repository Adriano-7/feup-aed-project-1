#ifndef TRABALHO_CLASSSCHEDULE_H
#define TRABALHO_CLASSSCHEDULE_H

#include <vector>
#include <set>
#include "Slot.h"
#include "UcClass.h"
#include "Student.h"

class ClassSchedule {
    public:
        ClassSchedule();
        ClassSchedule(UcClass ucClass);
        ClassSchedule(string ucId, string classId);
        UcClass getUcClass() const;
        void addSlot(Slot slot);
        const vector<Slot> &getSlots() const;
        int getNumStudents() const;
        void addStudent(Student student);
        bool sameUC(ClassSchedule other) const;
        bool operator < (const ClassSchedule &other) const;
        bool operator == (const ClassSchedule &other) const;
        void printHeader() const;
        void printSlots() const;
        void printStudents(string order = "alphabetical") const;
        void print() const;

    private:
        UcClass ucClass;
        vector<Slot> slots;
        set<Student> students;
};

#endif //TRABALHO_CLASSSCHEDULE_H
