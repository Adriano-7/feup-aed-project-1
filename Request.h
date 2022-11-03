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
        void print() const;
        Student getStudent() const;
        UcClass getDesiredClass() const;

    private:
        /** @brief Student that made the request */
        Student student;
        /** @brief Class that the student wants to enroll in */
        UcClass desiredClass;
};

#endif //TRABALHO_REQUEST_H
