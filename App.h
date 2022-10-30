#ifndef TRABALHO_APP_H
#define TRABALHO_APP_H

#include "ScheduleManager.h"

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
        void waitForInput() const;

    private:
        ScheduleManager manager;
};



#endif //TRABALHO_APP_H
