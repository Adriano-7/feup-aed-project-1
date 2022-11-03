#ifndef TRABALHO_UCCLASS_H
#define TRABALHO_UCCLASS_H

#include <string>

using namespace std;

/**
 * @brief Class to store the information about a given class in a UC
 * @param id
 * @param classId
 */


class UcClass{
    public:
        UcClass();
        UcClass(const string &ucId, const string &classId);
        string getUcId() const;
        string getClassId() const;
        bool operator ==(const UcClass &other) const;
        bool sameUC(const UcClass &other) const;
        bool operator < (const UcClass &other) const;
        bool operator > (const UcClass &other) const;

    private:
        /** @brief Id of the UC */
        string ucId;
        /** @brief Id of the class */
        string classId;
};

#endif //TRABALHO_UCCLASS_H
