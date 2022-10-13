#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <climits>
#include "Lesson.h"


using namespace std;


vector<Lesson> read_csv_lesson (){


    string fname =  "../schedule/classes.csv";

    int i = 0;
    vector<string> row;
    vector<Lesson> lessons;
    string line, word;

    fstream file (fname, ios::in);
    if(file.is_open())
    {
        file.ignore(LONG_MAX, '\n');
        cout << "File " << "classes" << " is open" << endl;

        while(getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while(getline(str, word, ','))//ClassCode,UcCode,Weekday,StartHour,Duration,Type
                row.push_back(word);

        Lesson lesson =Lesson(row[0], row[1], row[2], stof(row[3]), stof(row[4]), row[5]);
        lessons.push_back(lesson);
        }

        }
    else cout<<"Could not open the file\n";
    return lessons;
}