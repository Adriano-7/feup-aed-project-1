#ifndef TRABALHO_LESSON_H
#define TRABALHO_LESSON_H

#include <string>
using namespace std;

class Lesson {
    public:
        Lesson(string class_no, string UCCode, string weekday, float beginTime, float duration, string type);
        string getUCCode() const;
        void setUCCode(string UCCode);
        string getWeekday() const;
        void setWeekday(string weekday);
        float getBeginTime() const;
        void setBeginTime(float beginTime);
        float getDuration() const;
        void setDuration(float duration);
        string getType() const;
        void setType(string type);
        bool operator < (const Lesson lesson);
        bool operator == (Lesson lesson);
    private:
        string UCCode;
        string weekday;
        float beginTime;
        float duration;
        string type;

};


#endif //TRABALHO_LESSON_H
