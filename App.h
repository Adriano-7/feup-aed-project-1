#ifndef TRABALHO_APP_H
#define TRABALHO_APP_H

#include "ScheduleManager.h"
/**
 * @brief Class to run the program.
 */
class App {
    public:
        explicit App(const ScheduleManager &manager);
        int optionsMenu() const;
        int run();
        void checkStudentSchedule() const;
        void checkClassSchedule() const;
        void checkClassStudents() const;
        void checkUcSchedule() const;
        void submitNewRequest();
        void checkUcStudents() const;
        void processPendingRequests();
        void saveInformation();
        void waitForInput() const;

    private:
        ScheduleManager manager;
        int sleepTime;
};



#endif //TRABALHO_APP_H
