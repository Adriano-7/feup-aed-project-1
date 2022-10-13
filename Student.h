#ifndef TRABALHO_STUDENT_H
#define TRABALHO_STUDENT_H

#include <string>
#include "Schedule.h"

using namespace std;

class Student {
    public:
        Student(string id, string name, Schedule schedule, double d);
        string getId() const;
        void setId(string id);
        string getName() const;
        void setName(string name);
        Schedule getSchedule() const;
        void setSchedule(Schedule schedule);
        bool operator < (const Student student);
        bool operator == (const Student &student1);
    private:
        string id;
        string name;
        Schedule schedule;
};


#endif //TRABALHO_STUDENT_H
