#ifndef TRABALHO_APP_H
#define TRABALHO_APP_H

#include "ScheduleManager.h"
/**
 * @brief Class to run the program.
 */
class App {
    public:
        /**
        * @brief Constructor, sleepTime is set to 800000 ms
        * @param ScheduleManager manager
        */
        explicit App(const ScheduleManager &manager);

        /**
        * @brief Function that runs the application, it calls the menu and the functions to read the files
        * @return 0 if the application was closed successfully
        */
        int run();

        /**
        * @brief Function that prints the main menu
        * @return the option chosen by the user
        */
        int optionsMenu() const;

        /**
        * @brief Asks the user to input the students's UP number and prints the schedule of that student
        */
        void checkStudentSchedule() const;

        /**
        * @brief Ask the user to insert the class code and prints the schedule of that class
        */
        void checkClassSchedule() const;

        /**
        * @brief Asks the user to insert the ucCode and classCode and prints the students enrolled
        */
        void checkClassStudents() const;

        /**
        * @brief Asks the user to insert the ucId and prints the schedule of that subject
        */
        void checkUcSchedule() const;

        /**
        * @brief Function that allows the student to submit a request to change a class
        */
        void submitNewRequest();

        /**
        * @brief Function that prints the students enrolled in a subject
        */
        void checkUcStudents() const;

        /**
         * @brief Function that processes all pending requests
         */
        void processPendingRequests();

        /**
         * @brief Function that writes the information to the files before closing the program
         */
        void saveInformation();

        /**
        * @brief Function that makes the program wait for user input to continue
        */
        void waitForInput() const;

    private:
        ScheduleManager manager;
        int sleepTime;
};



#endif //TRABALHO_APP_H
