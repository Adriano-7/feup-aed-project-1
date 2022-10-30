#ifndef TRABALHO_STUDENT_H
#define TRABALHO_STUDENT_H

#include <string>
#include <vector>
#include "UcClass.h"

using namespace std;
/**
 * @brief Class that represents a student
 * @details Class that represents a student
 */
class Student {
    public:
        Student();
        Student(string id, string name);
        string getId() const;
        string getName() const;
        vector<UcClass> getClasses() const;
        void addClass(UcClass newClass);
        bool operator == (const Student &other) const;
        bool operator < (const Student &other) const;
        bool operator > (const Student &other) const;
        void print();

    private:
        string id;
        string name;
        vector<UcClass> classes;
};


#endif //TRABALHO_STUDENT_H
