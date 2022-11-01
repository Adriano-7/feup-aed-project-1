#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_map>
#include <csignal>

#include "ScheduleManager.h"

/**
 * @brief Schedule Manager constructor
 *
 */
ScheduleManager::ScheduleManager() {
    this->students = set<Student>();
    this->schedules = vector<ClassSchedule>();
    this->requests = queue<Request>();
}

/**
 * @brief Reads the files and creates the students and schedules
 *
 */
void ScheduleManager::readFiles() {
    createSchedules();
    setSchedules();
    createStudents();
}

/**
 * @brief Creates the schedules
 * Reads the file "classes_per_uc.csv" and creates a vector of schedules with only the uc code and the number of classe
 */
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

/**
 * @brief Sets the schedules
 * Reads the file "classes.csv" and adds the slots to the schedules created in the previous function
 * @see createSchedules()
 */

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

/**
 * @brief Reads the students_classes.csv file and creates the students set
 * @details The students are created with the student id, name and the classes they are enrolled in
 *
 * @return void
 */
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
/**
 * @brief Function that returns the index of the schedule with the ucClass passed as parameter
 * @param ucClass
 * @details Uses binary search to find the schedules
 *
 */
unsigned long ScheduleManager::binarySearchSchedules(const UcClass &desiredUcCLass) const{
    unsigned long left = 0, right = schedules.size() - 1, middle = (left + right) / 2;

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
    ClassSchedule* cs1 = findSchedule(c1);
    ClassSchedule* cs2 = findSchedule(c2);
    for(const Slot &slot1 : cs1->getSlots()){
        for(const Slot &slot2 : cs2->getSlots()){
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

ClassSchedule* ScheduleManager::findSchedule(const UcClass &ucClass) const {
    int index = binarySearchSchedules(ucClass);
    if(index == -1) return nullptr;
    return const_cast<ClassSchedule*>(&schedules[index]);
}


Student* ScheduleManager::findStudent(const string &studentId) const{
    auto student = students.find(Student(studentId, ""));
    return student == students.end() ? nullptr : const_cast<Student*>(&(*student));
}

void ScheduleManager::addRequest(const Student &student, const UcClass &ucClass) {
    requests.push(Request(student, ucClass));
}

void ScheduleManager::addRequest(const Request &request) {
    requests.push(request);
}

void insertIntoWeek(vector<vector<pair<string, Slot>>> &weekdays , const vector<pair<string, Slot>> &slots){
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

void groupDuplicates(vector<vector<pair<string, Slot>>> &weekdays){
    for (int i = 0; i < weekdays.size(); i++) {
        for (int j = 0; j < weekdays[i].size(); j++) {
            for (int k = j + 1; k < weekdays[i].size(); k++) {
                if (weekdays[i][j].second == weekdays[i][k].second) {
                    weekdays[i][j].first += ", " + weekdays[i][k].first;
                    weekdays[i].erase(weekdays[i].begin() + k);
                    k--;
                }
            }
        }
    }
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

void ScheduleManager::printStudentSchedule(const string &studentId) const {
    system("clear");
    Student* student = findStudent(studentId);

    if(student == nullptr){
        cout << ">> Student not found" << endl;
        return;
    }
    vector<vector<pair<string, Slot>>> weekdays(5);
    vector<UcClass> studentClasses = student->getClasses();

    vector<string> weekdaysNames = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    cout << endl <<  ">> The student " << student->getName() << " with UP number " << student->getId()
         << " is enrolled in the following classes:" << endl;

    student->printClasses();

    for (const UcClass &ucClass: studentClasses) {
        ClassSchedule *cs = findSchedule(ucClass);
        vector<pair<string, Slot>> slots;
        for (const Slot &slot: cs->getSlots()) {
            slots.emplace_back(cs->getUcClass().getUcId(), slot);
        }
        insertIntoWeek(weekdays, slots);
    }

    cout << endl << ">> The student's schedule is:" << endl;
    for (int i = 0; i < weekdays.size(); i++) {
        sort(weekdays[i].begin(), weekdays[i].end(), [](const pair<string, Slot> &a, const pair<string, Slot> &b) {
            return a.second.getStartTime() < b.second.getStartTime();
        });
        cout << "   >> " << weekdaysNames[i] << ": " << endl;

        for (const pair<string, Slot> &slot: weekdays[i]) {
            cout << "      " << slot.first << "   " << decimalToHours(slot.second.getStartTime()) << " to "
                 << decimalToHours(slot.second.getEndTime())
                 << "   " << slot.second.getType() << endl;
        }
    }
}


struct slotUcID{
    Slot slot;
    string ucID;
};

void ScheduleManager::printClassSchedule(const string &classCode) const{
    system("clear");
    map<string, vector<slotUcID>> slots;
    const vector<ClassSchedule> check = schedules;
    for(const ClassSchedule &cs : schedules){
        if(cs.getUcClass().getClassId() == classCode){
            for(const Slot &slot : cs.getSlots()){
                slotUcID hey = {slot, cs.getUcClass().getUcId()};
                slots[slot.getWeekDay()].push_back(hey);
            }
        }
    }

    if(slots.empty()){
        cout<<">> Class not found"<<endl;
        return;
    }

    cout << ">> The schedule for the class " << classCode << " is:" << endl;
    vector<string> weekdays {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    for(const string &weekday : weekdays){
        cout << "   >> " << weekday << ": " << endl;
        vector<slotUcID> slotsWeekday = slots[weekday];
        sort(slotsWeekday.begin(),slotsWeekday.end(), [](const slotUcID &s1, const slotUcID &s2){
                                                                    return s1.slot.getStartTime() < s2.slot.getStartTime();
        });
        for(const slotUcID &slotId : slotsWeekday){
            cout << "      " << decimalToHours(slotId.slot.getStartTime()) << " to " << decimalToHours(slotId.slot.getEndTime()) << "\t" << slotId.ucID <<  "\t" << slotId.slot.getType() << endl;
        }
    }
}

void ScheduleManager::printUcSchedule(const string &subjectCode) const{
    vector<ClassSchedule> schedulesUC;
    for (const ClassSchedule &cs: schedules) {
        if (cs.getUcClass().getUcId() == subjectCode) {
            schedulesUC.push_back(cs);
        }
    }
    if(schedulesUC.empty()){
        cout << ">> Subject not found" << endl;
        return;
    }
    vector<vector<pair<string, Slot>>> weekdays(5);
    vector<string> weekdaysNames = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    for (auto it = schedulesUC.begin(); it != schedulesUC.end(); it++) {
        vector <pair<string, Slot>> slots;
        for (const Slot &slot: it->getSlots()) {
            slots.emplace_back(it->getUcClass().getClassId(), slot);
        }

        insertIntoWeek(weekdays, slots);
        groupDuplicates(weekdays);
    }
    cout << endl << ">> This UC schedule is:" << endl;

    for (int i = 0; i < weekdays.size(); i++) {
        sort(weekdays[i].begin(), weekdays[i].end(), [](const pair<string, Slot> &a,const pair <string, Slot> &b) {
            return a.second.getStartTime() < b.second.getStartTime();
        });
        cout << "   >> " << weekdaysNames[i] << ": " << endl;

        for (const pair<string, Slot> &slot: weekdays[i]) {
            cout << "      " << decimalToHours(slot.second.getStartTime()) << " to "
                             << decimalToHours(slot.second.getEndTime()) << "\t" << slot.second.getType() << "\t" << slot.first << endl;
        }
    }
}

const vector<ClassSchedule> &ScheduleManager::getSchedules() const {
    return schedules;
}

const set<Student> &ScheduleManager::getStudents() const {
    return students;
}