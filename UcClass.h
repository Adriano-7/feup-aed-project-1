#ifndef TRABALHO_UCCLASS_H
#define TRABALHO_UCCLASS_H

#include <string>

using namespace std;

/**
 * @brief Class to store the information about a given class in a UC
 */
class UcClass{
    public:
        UcClass();
        UcClass(const string &ucId, const string &classId);
        bool sameUcId(const UcClass &other) const;
        string getUcId() const;
        string getClassId() const;
        string ucIdToString() const;
        bool operator ==(const UcClass &other) const;
        bool operator < (const UcClass &other) const;
        bool operator > (const UcClass &other) const;

    private:
        /** @brief Id of the UC */
        string ucId;
        /** @brief Id of the class */
        string classId;
};

#endif //TRABALHO_UCCLASS_H
