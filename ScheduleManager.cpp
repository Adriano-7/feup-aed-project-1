#include <set>
#include <iostream>
#include <sstream>
#include <fstream>

#include "ScheduleManager.h"

void ScheduleManager::createSchedules(){
    fstream file("../data/classes_per_uc.csv");
    file.ignore(1000, '\n');
    vector<string> row;
    string line, word;
    while (getline(file, line)) {
        if(line[line.size()-1] == '\r')
            line.resize(line.size()-1);
        row.clear();
        stringstream str(line);
        while(getline(str, word, ','))
            row.push_back(word);
        UcClass ucClass(row[0], row[1]);
        ClassSchedule cs(ucClass);
        schedules.push_back(cs);
    }
}

void ScheduleManager::setSchedules(){
    fstream file("../data/classes.csv");
    file.ignore(1000, '\n');
    vector<string> row;
    string line, word;
    while (getline(file, line)) {
        row.clear();
        if(line[line.size()-1] == '\r')
            line.resize(line.size()-1);
        stringstream str(line);
        while(getline(str, word, ','))
            row.push_back(word);
        string classCode = row[0], ucCode = row[1], weekDay = row[2], startTime = row[3], duration = row[4], type = row[5];
        UcClass ucClass(ucCode, classCode);
        Slot slot(weekDay,stof(startTime),stof(duration), type);

        // Algoritmo de pesquisa inefiicente (deve ser trocado)
        for (ClassSchedule &schedule : schedules) {
            if(ucClass == schedule.getUcClass()){
                schedule.addSlot(slot);
            }
        }

        // schedules[ucCLass].addSlot(slot);
        // procurar no schedules o elemento com o ucclass lido na linha
        // adicionar o slot lido na linha ao vector de slots do schedules para aquela ucclass
    }
}
    void ScheduleManager::createStudents() {
        fstream file("../data/students_classes.csv");
        file.ignore(1000, '\n');
        vector<string> row;
        string line, word;
        while (getline(file, line)) {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            UcClass newClass = UcClass(row[2], row[3]);
            vector<UcClass> classes;
            classes.push_back((newClass));
            Student student = Student(row[0],row[1], classes);

        }
    }

void ScheduleManager::readFiles() {
    createSchedules();
    setSchedules();
    createStudents();
}

void ScheduleManager::printSchedules() const {
    for (const ClassSchedule &cs : schedules) {
        UcClass ucClass = cs.getUcClass();
        cout << ucClass.getUcId() << " " << ucClass.getClassId() << " ";
        for (const Slot &s : cs.getSlots()) {
            cout << s.getWeekday() << " " << s.getBeginTime() << " " << s.getDuration() << " " << s.getType() << endl;
        }
    }
}

ScheduleManager::ScheduleManager() {
    this->students = set<Student>();
    this->schedules = vector<ClassSchedule>();
    this->requests = queue<Request>();
}

