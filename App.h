#ifndef TRABALHO_APP_H
#define TRABALHO_APP_H

#include "ScheduleManager.h"
/**
 * @brief Class that represents the application
 * @details This class is responsible for the application's main loop
 */
class App {
    public:
        explicit App(const ScheduleManager &manager);
        int run();
        int optionsMenu() const;
        void checkStudentSchedule() const;
        void checkClassSchedule() const;
        void checkClassStudents() const;
        void checkUcSchedule() const;
        void submitNewRequest();
        void checkUcStudents() const;
        void processPendingRequests();
        void waitForInput() const;

    private:
        ScheduleManager manager;
        int sleepTime;
};



#endif //TRABALHO_APP_H
