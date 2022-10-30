#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "ScheduleManager.h"

ScheduleManager::ScheduleManager() {
    this->students = set<Student>();
    this->schedules = vector<ClassSchedule>();
    this->requests = queue<Request>();
}

void ScheduleManager::readFiles() {
    createSchedules();
    setSchedules();
    createStudents();
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
        int scheduleIndex = binarySearchSchedules(ucClass);
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
        int i = binarySearchSchedules(newUcClass);
        Student student(id, name);

        if (students.find(student) == students.end()) {
            student.addClass(this->schedules[i].getUcClass());
            students.insert(student);
        } else {
            auto loc = students.find(student);
            Student modStudent = *loc;
            students.erase(loc);
            modStudent.addClass(this->schedules[i].getUcClass());
            students.insert(modStudent);
        }
        this->schedules[i].addStudent(student);
    }
}

int ScheduleManager::binarySearchSchedules(const UcClass &desiredUcCLass) const{
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

bool ScheduleManager::classesCollide(const UcClass &c1, const UcClass &c2) const{
    if(c1.sameUC(c2)) return false;
    ClassSchedule cs1 = schedules[binarySearchSchedules(c1)];
    ClassSchedule cs2 = schedules[binarySearchSchedules(c2)];
    for(const Slot &slot1 : cs1.getSlots()){
        for(const Slot &slot2 : cs2.getSlots()){
            if(slot1.collides(slot2)) return true;
        }
    }
    return false;
}

bool ScheduleManager::requestHasCollision(const Request &request) const{
    Student student = request.getStudent();
    UcClass desiredClass = request.getDesiredClass();
    vector<UcClass> studentClasses = student.getClasses();
    for (const UcClass &ucClass : studentClasses){
        if(classesCollide(ucClass, desiredClass)) return true;
    }
    return false;
}

bool ScheduleManager::ucClassExists(const string &ucCode, const string &classCode) const {
    UcClass ucClass = UcClass(ucCode, classCode);
    int index = binarySearchSchedules(ucClass);
    return index != -1;
}

bool ScheduleManager::studentExists(const string &studentId) const{
    auto student = students.find(Student(studentId, ""));
    return student != students.end();
}

Student ScheduleManager::findStudent(const string &studentId) const{
    auto student = students.find(Student(studentId, ""));
    return student == students.end() ? Student() : *student;
}

void ScheduleManager::addRequest(const Student &student, const UcClass &ucClass) {
    requests.push(Request(student, ucClass));
}

void ScheduleManager::addRequest(const Request &request) {
    requests.push(request);
}

string decimalToHours(int decimal){
    double time = decimal;
    int timeMins = (int)floor( time * 60.0 );
    int hours = timeMins / 60;
    int minutes = timeMins % 60;
    string hoursStr = to_string(hours);
    string minutesStr = to_string(minutes);
    if (hours < 10) hoursStr = "0" + hoursStr;
    if (minutes < 10) minutesStr = "0" + minutesStr;
    return hoursStr + ":" + minutesStr;
}

void ScheduleManager::printStudentSchedule(const string &studentId) const{

    Student student = findStudent(studentId);

    vector<UcClass> studentClasses = student.getClasses();
    vector<vector<pair<string, Slot>>> weekdays = vector<vector<pair<string, Slot>>>(5);
    vector<string> weekdaysNames = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    system("clear");
    cout << endl <<  ">> The student " << student.getName() << " with UP number " << student.getId()
         << " is enrolled in the following classes:" << endl;

    for (const UcClass &ucClass: studentClasses) {
        cout << "   " << ucClass.getUcId() << " " << ucClass.getClassId() << "  |  ";
    }
    cout << endl;

    for (const UcClass &ucClass: studentClasses) {
        ClassSchedule cs = getSchedules()[binarySearchSchedules(ucClass)];
        vector<pair<string, Slot>> slots;
        for (const Slot &slot: cs.getSlots()) {
            slots.emplace_back(cs.getUcClass().getUcId(), slot);
        }

        for (const pair<string, Slot> &slot: slots) {
            if (slot.second.getWeekDay() == "Monday") {
                weekdays[0].push_back(slot);
            } else if (slot.second.getWeekDay() == "Tuesday") {
                weekdays[1].push_back(slot);
            } else if (slot.second.getWeekDay() == "Wednesday") {
                weekdays[2].push_back(slot);
            } else if (slot.second.getWeekDay() == "Thursday") {
                weekdays[3].push_back(slot);
            } else if (slot.second.getWeekDay() == "Friday") {
                weekdays[4].push_back(slot);
            }
        }
    }

    cout << endl << ">> The student's schedule is:" << endl;
    for (int i = 0; i < weekdays.size(); i++) {
        sort(weekdays[i].begin(), weekdays[i].end(), [](const pair<string, Slot> &a, const pair<string, Slot> &b) {
            return a.second.getStartTime() < b.second.getStartTime();
        });
        cout << "   >> "<< weekdaysNames[i] << ": " << endl;

        for (const pair<string, Slot> &slot: weekdays[i]) {
            cout << "      " << slot.first << "   " << decimalToHours(slot.second.getStartTime()) << " to " << decimalToHours(slot.second.getEndTime())
                 << "   " << slot.second.getType() << endl;
        }
    }
}

const vector<ClassSchedule> &ScheduleManager::getSchedules() const {
    return schedules;
}

const set<Student> &ScheduleManager::getStudents() const {
    return students;
}