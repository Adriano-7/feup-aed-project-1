#include "ScheduleManager.h"
#include "Test.h"
#include "App.h"

using namespace std;

int main()
{
    ScheduleManager manager;
    manager.readFiles();
    Test tester;
    //tester.printSchedules(manager);
    //tester.printStudents(manager);
    App app(manager);
    app.run();
    return 0;
}
