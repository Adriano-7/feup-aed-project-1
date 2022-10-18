#include <set>
#include <climits>
#include <iostream>
#include <sstream>
#include <fstream>

#include "ScheduleManager.h"

void ScheduleManager::create_schedules(){
    ifstream file("../data/classes_per_uc.csv");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string ucId, classId;
        iss >> ucId >> classId;
        UcClass ucClass(ucId, classId);
        ClassSchedule cs(ucClass);
        schedules.push_back(cs);
    }
}

void ScheduleManager::setSchedules(){
    ifstream file("../data/classes.csv");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string classCode, ucCode, weekday, startTime, duration, type;
        iss >> classCode >> ucCode >> weekday >> startTime >> duration >> type;
        UcClass ucClass(classCode, ucCode);
        Slot slot(weekday,stoi(startTime),stoi(duration), type);
        for (ClassSchedule &cs : schedules) {
            if(cs.getUcClass() == ucClass){
                cs.addSlot(slot);
            }
        }
        // schedules[ucCLass].addSlot(slot);
        // procurar no schedules o elemento com o ucclass lido na linha
        // adicionar o slot lido na linha ao vector de slots do schedules para aquela ucclass
    }
}

void ScheduleManager::readFiles() {
    create_schedules();
    setSchedules();
}



/* 
    string fname =  "../data/classes.csv";

    int i = 0;
    vector<string> row;
    vector<Slot> lessons;
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

            ClassSchedule cs = ClassSchedule
            Slot slot = Slot(row[2], stof(row[3]), stof(row[4]), row[5]);
            
        }

    }
    else cout<<"Could not open the file\n";
    return lessons;
}
readUc
 
 */