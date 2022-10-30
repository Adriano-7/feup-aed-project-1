#ifndef TRABALHO_UCCLASS_H
#define TRABALHO_UCCLASS_H

#include <string>

using namespace std;

/**
 * A class to store the information about a given class in a UC
 */

class UcClass{
    public:
        /**Default Constructor, ucId and classId set to empty string*/
        UcClass();

        /**Constructor
         * @param ucId the id of the UC
         * @param classId the id of the class
         */
        UcClass(const string &ucId, const string &classId);

        /**Get the id of the UC
         */
        string getUcId() const;

        /**Get the id of the class
         */
        string getClassId() const;

        /** Compares two UcClass
         * @param other The UcClass to compare to
         * @return true if the ucId and classId are the same, false otherwise
         */
        bool operator ==(const UcClass &other) const;

        /** Compares two UcClass
         * @param other The UcClass to compare to
         * @return true if the ucId is the same, false otherwise
         */
        bool sameUC(const UcClass &other) const;

        /** Compares two UcClass
         * @param other The UcClass to compare to
         * @return true if the ucId is smaller or if the ucId is the same and the classId is smaller, false otherwise
         */
        bool operator < (const UcClass &other) const;

        /** Compares two UcClass
         * @param other The UcClass to compare to
         * @return true if the ucId is bigger or if the ucId is the same and the classId is bigger, false otherwise
         */
        bool operator > (const UcClass &other) const;

    private:
        string ucId;
        string classId;
};

#endif //TRABALHO_UCCLASS_H
