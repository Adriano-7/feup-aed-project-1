#ifndef TRABALHO_REQUEST_H
#define TRABALHO_REQUEST_H

#include "Student.h"

class Request{
    public:
        Request(Student student, UcClass desiredClass);
        Student getStudent() const;
        UcClass getDesiredClass() const;

    private:
        Student student;
        UcClass desiredClass;
};

#endif //TRABALHO_REQUEST_H
