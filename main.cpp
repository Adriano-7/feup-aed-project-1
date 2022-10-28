#include "ScheduleManager.h"
#include "Test.h"
#include "App.h"

using namespace std;

int main()
{
    ScheduleManager manager;
    //Test tester(manager);
    //tester.printSchedules();
    //tester.printStudents();
    App app(manager);
    app.run();
    return 0;
}
