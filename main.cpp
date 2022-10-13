#include "read_csv.cpp"

#include "Student.h"


using namespace std;

int main()
{
    Schedule schedule;
    Student francisco = Student("202108762", "Francisco", schedule, 70.0);
    vector<Lesson> lessons = read_csv_lesson();
    cout << (lessons[0].getUCCode());
    return 0;
}
