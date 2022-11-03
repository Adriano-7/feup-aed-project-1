#ifndef TRABALHO_SLOT_H
#define TRABALHO_SLOT_H

#include <string>
#include <vector>

using namespace std;
/**
 * @brief Class that represents a slot (time and day) in which a class of a given course is held.
 * @param duration
 * @param startTime
 * @param endTime
 * @param type
 */

class Slot {
    public:
        Slot(const string &weekDay, const float &beginTime, const float &duration, const string &type);
        string getWeekDay() const;
        string getType() const;
        float getStartTime() const;
        float getEndTime() const;
        bool collides(const Slot &other) const;
        bool operator !=(const Slot &other) const;
        bool operator ==(const Slot &other) const;

    private:
        string weekDay;
        float startTime;
        float endTime;
        /**
         * @brief Type of the class
         * T - Teórica
         * P - Prática
         * PL - Prática Laboratorial
         */
        string type;
};


#endif //TRABALHO_SLOT_H
