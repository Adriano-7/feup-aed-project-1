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
        bool operator ==(const UcClass &other) const;
        bool operator < (const UcClass &other) const;

    private:
        string ucId;
        string classId;
};
#endif //TRABALHO_UCCLASS_H
