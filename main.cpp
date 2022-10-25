#include "ScheduleManager.h"

using namespace std;

int main()
{
    ScheduleManager manager;
    manager.readFiles();
    manager.students[0].printStudent();
    return 0;
}
