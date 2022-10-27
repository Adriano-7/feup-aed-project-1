#ifndef TRABALHO_STUDENT_H
#define TRABALHO_STUDENT_H

#include <string>
#include <vector>
#include "UcClass.h"

using namespace std;

class Student {
    public:
        Student(string id, string name, vector<UcClass> classes);
        string getId() const;
        string getName() const;
        vector<UcClass> getClasses() const;
        void addUcClass (UcClass ucClass);
        bool operator == (const Student &other);
        bool operator < (const Student &other);
        bool operator > (const Student &other);


    private:
        string id;
        string name;
        vector<UcClass> classes;
};


#endif //TRABALHO_STUDENT_H
