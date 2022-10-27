#include "ScheduleManager.h"
#include "Test.h"

using namespace std;

int main()
{
    ScheduleManager manager;
    Test tester;
    manager.readFiles();
    tester.printSchedules(manager);
    return 0;
}