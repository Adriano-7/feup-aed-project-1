#include "ScheduleManager.h"
#include <iostream>
using namespace std;

int main()
{
    ScheduleManager manager;
    manager.readFiles();
    manager.printSchedules();
    return 0;
}
