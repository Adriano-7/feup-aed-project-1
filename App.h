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
        void waitForInput() const;
        static const int sleepTime = 800000;

    private:
        ScheduleManager manager;

    int optionsMenu();
};



#endif //TRABALHO_APP_H
