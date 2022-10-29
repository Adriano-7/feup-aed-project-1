#ifndef TRABALHO_APP_H
#define TRABALHO_APP_H

#include "ScheduleManager.h"

class App {
    public:
        App(ScheduleManager manager);
        int run();
        int optionsMenu();
        void checkStudentSchedule();
        void checkClassSchedule();
        void checkClassStudents();
        void checkUcSchedule();
        void submitNewRequest();
        void waitForInput();

    private:
        ScheduleManager manager;
};



#endif //TRABALHO_APP_H
