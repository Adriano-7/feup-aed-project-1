#ifndef TRABALHO_CLASS_H
#define TRABALHO_CLASS_H

#include <string>
#include <set>
#include "Schedule.h"
#include "Student.h"

using namespace std;

class Class {
    public:
        Class(string id, Schedule schedule, set<Student> students);
        string getId() const;
        void setId(string id);
        Schedule getSchedule() const;
        void setSchedule(Schedule schedule);
        set<Student> getStudents() const;
        void setStudents(set<Student> students);
        void addStudent(Student student);
        void removeStudent(Student student);
    private:
        string id;
        Schedule schedule;
        set<Student> students;
        int occupation;
};


#endif //TRABALHO_CLASS_H
