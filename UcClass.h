#ifndef TRABALHO_UCCLASS_H
#define TRABALHO_UCCLASS_H

#include <string>

using namespace std;

class UcClass{
    public:
        UcClass();
        UcClass(string ucId, string classId);
        string getUcId() const;
        string getClassId() const;
        int getNumStudents() const;
        void incrementNumStudents();
        void decrementNumStudents();
        bool operator ==(const UcClass &other) const;
        bool operator < (const UcClass &other) const;
        bool operator > (const UcClass &other) const;
        bool sameUC(UcClass other) const;

    private:
        string ucId;
        string classId;
        int numStudents;
};

#endif //TRABALHO_UCCLASS_H
