#ifndef TRABALHO_REQUEST_H
#define TRABALHO_REQUEST_H

#include "Student.h"
#include <iostream>

/**
 * @brief Class to store the information about a given request.
 */

class Request{
    public:

        /**
        * @brief Constructor of the Request class
        * @param student Student that made the request
        * @param desiredClass Class that the student wants to enroll in
        */
        Request(const Student &student, const UcClass &desiredClass);

        /**
        * @brief Getter of the student that made the request
        * @return Student that made the request
        */
        Student getStudent() const;

        /**
        * @brief Getter of the class that the student wants to enroll in
        * @return Class that the student wants to enroll in
        */
        UcClass getDesiredClass() const;

        /**
        * @brief Prints the request
        */
        void print() const;

    private:
        Student student;
        UcClass desiredClass;
};

#endif //TRABALHO_REQUEST_H
