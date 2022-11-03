#ifndef TRABALHO_STUDENT_H
#define TRABALHO_STUDENT_H

#include <string>
#include <vector>
#include "UcClass.h"

using namespace std;
/**
 * @brief Class to store the information about a given student.

 * @param id
 * @param name
 * @param classes
 */

class Student {
    public:
        Student();
        Student(const string &id, const string &name);
        string getId() const;
        string getName() const;
        vector<UcClass> getClasses() const;
        void addClass(const UcClass &newClass);
        UcClass changeClass(const UcClass &newClass);
        bool isEnrolled(const string &ucCode) const;
        bool operator == (const Student &other) const;
        bool operator < (const Student &other) const;
        bool operator > (const Student &other) const;
        void printHeader() const;
        void printClasses() const;
        void print() const;

    private:
        string id;
        string name;
        vector<UcClass> classes;
};


#endif //TRABALHO_STUDENT_H
