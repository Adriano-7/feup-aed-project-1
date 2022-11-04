#include "ScheduleManager.h"
#include "App.h"

using namespace std;

int main()
{
    system("clear");
    ScheduleManager manager;
    App app(manager);
    app.run();
    return 0;
}
