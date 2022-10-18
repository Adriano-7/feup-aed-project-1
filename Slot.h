#ifndef TRABALHO_SLOT_H
#define TRABALHO_SLOT_H

#include <string>
#include <vector>

using namespace std;

class Slot {
    public:
        Slot(string weekday, float beginTime, float duration, string type);
        string getWeekday() const;
        float getBeginTime() const;
        float getDuration() const;
        string getType() const;

    private:
        string weekday;
        float beginTime;
        float endTime;
        string type;
};


#endif //TRABALHO_SLOT_H
