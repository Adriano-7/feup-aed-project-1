#ifndef TRABALHO_CLASS_H
#define TRABALHO_CLASS_H

#include <string>
#include <vector>
#include "Student.h"

using namespace std;

class Class {
    public:
        Class(string id, Schedule schedule, vector<Student> students);
        string getId() const;
        void setId(string id);
        Schedule getSchedule() const;
        void setSchedule(Schedule schedule);
        vector<Student> getStudents() const;
        void setStudents(vector<Student> students);
        void addStudent(Student student);
        void removeStudent(Student student);

    private:
        string id;
        Schedule schedule;
        vector<Student> students;
        int occupation;
};


#endif //TRABALHO_CLASS_H
