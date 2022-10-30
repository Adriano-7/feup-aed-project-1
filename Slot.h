#ifndef TRABALHO_SLOT_H
#define TRABALHO_SLOT_H

#include <string>
#include <vector>

using namespace std;

class Slot {
    public:
        Slot(string weekday, float beginTime, float duration, string type);
        string getWeekDay() const;
        string getType() const;
        float getStartTime() const;
        float getEndTime() const;
        bool collides(Slot other) const;
        bool operator !=(const Slot &other) const;
        bool operator ==(const Slot &other) const;

    private:
        string weekday;
        float startTime;
        float endTime;
        string type;
};


#endif //TRABALHO_SLOT_H
