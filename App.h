//
// Created by evans24 on 27-10-2022.
//

#ifndef TRABALHO_APP_H
#define TRABALHO_APP_H


#include "ScheduleManager.h"

class App {
private:
    ScheduleManager manager;
public:
    App(ScheduleManager manager);
    void run();
};



#endif //TRABALHO_APP_H
