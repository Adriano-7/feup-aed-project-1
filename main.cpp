#include "ScheduleManager.h"

using namespace std;

int main()
{
    ScheduleManager manager;
    manager.readFiles();
    manager.printSchedules();

    return 0;
}
