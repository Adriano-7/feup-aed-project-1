#include <set>
#include <iostream>
#include <sstream>
#include <fstream>

#include "ScheduleManager.h"

int ScheduleManager::BSearchSchedules(UcClass desiredUcCLass){
    int left = 0;
    int right = schedules.size() - 1;
    int middle = (left + right) / 2;

    while(left <= right){
        if(schedules[middle].getUcClass() == desiredUcCLass){
            return middle;
        }
        else if(schedules[middle].getUcClass() < desiredUcCLass){
            left = middle + 1;
        }
        else{
            right = middle - 1;
        }
        middle = (left + right) / 2;
    }
    return -1;
}

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

void ScheduleManager::setSchedules() {
    fstream file("../data/classes.csv");
    file.ignore(1000, '\n');
    vector<string> row;
    string line, word;
    while (getline(file, line)) {
        row.clear();
        if (line[line.size() - 1] == '\r')
            line.resize(line.size() - 1);
        stringstream str(line);
        while (getline(str, word, ','))
            row.push_back(word);

        string classCode = row[0], ucCode = row[1], weekDay = row[2], startTime = row[3], duration = row[4], type = row[5];
        UcClass ucClass(ucCode, classCode);
        Slot slot(weekDay, stof(startTime), stof(duration), type);
        int scheduleIndex = BSearchSchedules(ucClass);
        if (scheduleIndex != -1) {
            schedules[scheduleIndex].addSlot(slot);
        }
    }
}
    void ScheduleManager::createStudents() {
        fstream file("../data/students_classes.csv");
        file.ignore(1000, '\n');
        vector<string> row;
        string line, word;
        while (getline(file, line)) {
            row.clear();
            if (line[line.size() - 1] == '\r')
                line.resize(line.size() - 1);
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            string id = row[0], name = row[1];
            UcClass newUcClass = UcClass(row[2], row[3]);
            Student student(id, name);
            if (students.find(student) == students.end()) {
                student.addUcClass(newUcClass);
                students.insert(student);
            } else {
                auto loc = students.find(student);
                Student modStudent = *loc;
                students.erase(loc);
                modStudent.addClass(newUcClass);
                students.insert(modStudent);
            }
        }
    }

void ScheduleManager::readFiles() {
    createSchedules();
    setSchedules();
    createStudents();
}

ScheduleManager::ScheduleManager() {
    this->students = set<Student>();
    this->schedules = vector<ClassSchedule>();
    this->requests = queue<Request>();
}

const vector<ClassSchedule> &ScheduleManager::getSchedules() const {
    return schedules;
}

const set<Student> &ScheduleManager::getStudents() const {
    return students;
}