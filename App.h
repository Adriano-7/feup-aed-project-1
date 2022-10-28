//
// Created by evans24 on 27-10-2022.
//

#ifndef TRABALHO_APP_H
#define TRABALHO_APP_H


#include "ScheduleManager.h"

class App {
    public:
        App(ScheduleManager manager);
        int run();
        int optionsMenu();
        void option1();
        void option2();
        void option3();
        void option4();
        void option5();
        void option6();
        void waitForInput();

    private:
        ScheduleManager manager;
};



#endif //TRABALHO_APP_H
