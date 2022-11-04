#ifndef TRABALHO_APP_H
#define TRABALHO_APP_H

#include "ScheduleManager.h"
/**
 * @brief Class to run the program.
 */
class App {
    public:
        explicit App(const ScheduleManager &manager);

        int run();
        void waitForInput() const;

        int optionsMenu() const;
        int requestsMenu() const;
        int sortingMenu() const;

        void checkStudentSchedule() const;
        void checkClassSchedule() const;
        void checkClassStudents() const;
        void checkUcSchedule() const;
        void checkUcStudents() const;

        void submitNewRequest(int option);
        void submitChangingRequest(Student* student);
        void submitRemovalRequest(Student* student);
        void submitEnrollmentRequest(Student* student);
        void processPendingRequests();
        void printPendingRequests() const;

        void saveInformation();

    private:
        /** @brief ScheduleManager object that stores all students, schedules and requests */
        ScheduleManager manager;
        /** @brief Variable that stores the suspend execution time in microseconds */
        int sleepTime;
};



#endif //TRABALHO_APP_H
