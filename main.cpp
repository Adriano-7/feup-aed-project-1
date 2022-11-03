#include "ScheduleManager.h"
#include "App.h"

using namespace std;

int main()
{
    ScheduleManager manager;
    App app(manager);
    app.run();
    return 0;
}
