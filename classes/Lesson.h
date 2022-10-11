#ifndef TRABALHO_LESSON_H
#define TRABALHO_LESSON_H

#include <string>
#include "Class.h"
using namespace std;

class Lesson {
    public:
        Lesson(string UCCode, string weekday, float beginTime, float duration, string type, Class _class);
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
        Class getClass() const;
        void setClass(Class _class);
    private:
        string UCCode;
        string weekday;
        float beginTime;
        float duration;
        string type;
        Class _class;
};


#endif //TRABALHO_LESSON_H
