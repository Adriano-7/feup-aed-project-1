#include "read_csv.cpp"

#include "Student.h"


using namespace std;

int main()
{
    Schedule schedule;
    Student francisco = Student("202108762", "Francisco", schedule, 70.0);
    read_csv("classes.csv");
    return 0;
}
