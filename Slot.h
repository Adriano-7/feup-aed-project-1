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
        bool operator < (const Slot lesson);
        bool operator == (Slot lesson);
        friend ostream& operator<< (ostream& out, const Slot& lesson);
        //vector lesson_filter_number(const vector<Slot>, string class);

    private:
        string weekday;
        float beginTime;
        float endTime;
        string type;
};


#endif //TRABALHO_SLOT_H
