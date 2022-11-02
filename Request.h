#ifndef TRABALHO_REQUEST_H
#define TRABALHO_REQUEST_H

#include "Student.h"
#include <iostream>

/**
 * @brief Class to store the information about a given request.
 */


class Request{
    public:
        Request(const Student &student, const UcClass &desiredClass);
        Student getStudent() const;
        UcClass getDesiredClass() const;
        void print() const;

    private:
        Student student;
        UcClass desiredClass;
};

#endif //TRABALHO_REQUEST_H
