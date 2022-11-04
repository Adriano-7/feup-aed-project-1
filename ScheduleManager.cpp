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
*@brief Schedule Manager constructor
* @details Creates a Schedule Manager with an empty set of students, a empty vector of schedules and a empty queue of changingRequests
*/
ScheduleManager::ScheduleManager() {
    this->students = set<Student>();
    this->schedules = vector<ClassSchedule>();
    this->changingRequests = queue<Request>();
    this->removalRequests = queue<Request>();
    this->enrollmentRequests = queue<Request>();
    this->rejectedRequests = vector<pair<Request, string>>();
}

/**
*@brief Reads the files and creates the objects
*/
void ScheduleManager::readFiles() {
    createSchedules();
    setSchedules();
    createStudents();
}

/**
*@brief Reads the file "classes_per_uc.csv" and creates a vector of schedules with only the uc code and the class code
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
* @brief Reads the file "classes.csv" and adds the slots to the schedules created in the previous function
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
        unsigned long scheduleIndex = binarySearchSchedules(ucClass);
        if (scheduleIndex != -1) {
            schedules[scheduleIndex].addSlot(slot);
        }
    }
}

/**
* @brief Reads the students_classes.csv file and creates the students set
* @details The students are created with the student id, name and the classes they are enrolled in
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
        unsigned long i = binarySearchSchedules(newUcClass);
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
* @param desiredUcCLass
* @details Uses binary search to find the schedules
* @return The index of the schedule with the ucClass passed as parameter
 * @see Slot::collides()
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

/**
* @brief Function that verifies if the schedule of two given classes have a conflict
* @return true if the classes have a conflict, false otherwise
*/
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

/**
* @brief Function that verifies if a given request has a conflict with the schedule of a given student
* @param request
* @return true if the request has a conflict with the schedule of the student, false otherwise
*/
bool ScheduleManager::requestHasCollision(const Request &request) const{
    Student student = request.getStudent();
    UcClass desiredClass = request.getDesiredClass();
    vector<UcClass> studentClasses = student.getClasses();
    for (const UcClass &ucClass : studentClasses){
        if(classesCollide(ucClass, desiredClass)) return true;
    }
    return false;
}

/**
* @brief Function that returns the student with the ID passed as parameter
* @param studentId
*/
Student* ScheduleManager::findStudent(const string &studentId) const{
    auto student = students.find(Student(studentId, ""));
    return student == students.end() ? nullptr : const_cast<Student*>(&(*student));
}

/**
* @brief Function that returns the schedule with the ucClass passed as parameter
* @param ucClass
*/
ClassSchedule* ScheduleManager::findSchedule(const UcClass &ucClass) const {
    unsigned long index = binarySearchSchedules(ucClass);
    if(index == -1) return nullptr;
    return const_cast<ClassSchedule*>(&schedules[index]);
}

/**
 * @brief Function that gets all classes of a given subject
 * @param subjectCode
 * @return A vector with all the classes of a given subject
 */
vector<ClassSchedule> ScheduleManager::classesOfSubject(const string &ucId) const {
    vector<ClassSchedule> classes;
    for(const ClassSchedule &cs : schedules){
        if(cs.getUcClass().getUcId() == ucId){
            classes.push_back(cs);
        }
    }
    return classes;
}

/**
 * @brief Function that gets all students of a given subject
 * @param subjectCode
 * @return A vector with all the students of a given subject
 */
vector<Student> ScheduleManager::studentsOfSubject(const string &ucId) const {
    vector<Student> subjectStudents;
    vector<ClassSchedule> subjectClasses = classesOfSubject(ucId);
    for(const ClassSchedule &cs : subjectClasses){
        for(const Student &student : cs.getStudents()){
            subjectStudents.push_back(student);
        }
    }
    return subjectStudents;
}

/**
 * @brief Function that given a student id and the ucClass he wants to change to, adds the request to the queue of changingRequests
 */
void ScheduleManager::addChangingRequest(const Student &student, const UcClass &ucClass) {
    changingRequests.push(Request(student, ucClass, "Changing"));
}

void ScheduleManager::addRemovalRequest(const Student &student, const UcClass &ucClass) {
    removalRequests.push(Request(student, ucClass, "Removal"));
}

void ScheduleManager::addEnrollmentRequest(const Student &student, const UcClass &ucClass) {
    enrollmentRequests.push(Request(student, ucClass, "Enrollment"));
}

/**
 * @brief Function that verifies if a request doesn't exceed the maximum number of students which can be enrolled in a given class
 * @param request
 * @return boolean expression
 */
bool ScheduleManager::requestExceedsMaxStudents(const Request &request) const {
    string ucId = request.getDesiredClass().getUcId();
    vector<ClassSchedule> subjectClasses = classesOfSubject(ucId);
    sort(subjectClasses.begin(), subjectClasses.end(), [](const ClassSchedule &cs1, const ClassSchedule &cs2){
        return cs1.getNumStudents() < cs2.getNumStudents();
    });
    int maxDifference = subjectClasses[subjectClasses.size() - 1].getNumStudents() - subjectClasses[0].getNumStudents();
    return maxDifference >= 4;
}

/**
 * @brief Function that processes the changingRequests in the queue
 */
void ScheduleManager::processChangingRequest(const Request &request) {
    if(requestHasCollision(request)){
        rejectedRequests.emplace_back(request, "Collision in the students' schedule");
    }
    else if(requestExceedsMaxStudents(request)){
        rejectedRequests.emplace_back(request, "Exceeds maximum number of students in the class");
    }
    else{
        Student* student = findStudent(request.getStudent().getId());
        UcClass ucClass = findSchedule(request.getDesiredClass())->getUcClass();
        UcClass oldClass = student->changeClass(ucClass);
        findSchedule(request.getDesiredClass())->addStudent(*student);
        findSchedule(oldClass)->removeStudent(*student);
        cout << "   "; request.printHeader();
    }
}

void ScheduleManager::processRemovalRequest(const Request &request) {
    Student* student = findStudent(request.getStudent().getId());
    UcClass ucClass = findSchedule(request.getDesiredClass())->getUcClass();
    student->removeSubject(ucClass.getUcId());
    findSchedule(ucClass)->removeStudent(*student);
    cout << "   "; request.printHeader(); cout << endl;
}

void ScheduleManager::processEnrollmentRequest(const Request &request) {
    if(requestHasCollision(request)){
        rejectedRequests.emplace_back(request, "Collision in the students' schedule");
    }
    else{
        Student* student = findStudent(request.getStudent().getId());
        UcClass ucClass = findSchedule(request.getDesiredClass())->getUcClass();
        student->addSubject(ucClass);
        findSchedule(ucClass)->addStudent(*student);
        cout << "   "; request.printHeader();
    }
    cout << endl;
}

/**
 * @brief Function that processes all changingRequests in the queue
 */
void ScheduleManager::processRequests() {
    cout << ">> Accepted removal requests:" << endl;
    while(!removalRequests.empty()){
        Request request = removalRequests.front();
        removalRequests.pop();
        processRemovalRequest(request);
    }
    cout << ">> Accepted changing requests:" << endl;
    while(!changingRequests.empty()){
        Request request = changingRequests.front();
        changingRequests.pop();
        processChangingRequest(request);
    }
    cout << ">> Accepted enrollment requests:" << endl;
    while(!enrollmentRequests.empty()){
        Request request = enrollmentRequests.front();
        enrollmentRequests.pop();
        processEnrollmentRequest(request);
    }
    if(!rejectedRequests.empty()){
        printRejectedRequests();
    }else{
        cout << ">> All changingRequests were accepted!" << endl;
    }
    string q;
    cout << endl << "Insert any key to continue: ";
    cin >> q;
    cout << endl;
    system("clear");
}

/**
 * @brief Function that writes all information to the files
 */
void ScheduleManager::writeFiles() const {
    ofstream file;
    file.open("../data/students_classes.csv");
    file << "StudentCode,StudentName,UcCode,ClassCode" << endl;
    for (const Student &s: students) {
        for (const UcClass &c: s.getClasses()) {
            file << s.getId() << "," << s.getName() << "," << c.getUcId() << "," << c.getClassId() << endl;
        }
    }
    file.close();
}

/**
 * @brief Function the organizes the slots in weekdays
 * @details The slots are organized in a vector in which the index is associated with the weekday.
 * The index 0 is associated with Monday, 1 with Tuesday, 2 with Wednesday...
 */
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
/**
 * @brief Function that organizes the slots by weekday
 * @param weekdays
 */
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
/**
 * @brief  Function converts decimal time to string
 * @param weekdays
 *
 */
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

/**
 * @brief Function that prints the schedule of a given student
 * @param studentId
 */
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
         << " is enrolled in the following classes:" << endl << "   ";

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

/**
 * @brief Function that prints the schedule of a given class
 * @param classCode
 */
void ScheduleManager::printClassSchedule(const string &classCode) const{
    system("clear");
    struct slotUcID{Slot slot; string ucID;};
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

/**
 * @brief Function that print the schedule of a given subject
 * @param subjectCode
 */
void ScheduleManager::printUcSchedule(const string &subjectCode) const{
    system("clear");
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
    cout << endl << ">> The subject "<< subjectCode << " has the following schedule:" << endl;

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

void ScheduleManager::printClassStudents(const UcClass &ucClass, const string &orderType) const{
    ClassSchedule* cs = findSchedule(ucClass);
    if(cs == nullptr){
        cout << ">> Class not found" << endl;
        return;
    }
    cs->printStudents(orderType);
}

/**
 * @brief Function that prints the students enrolled a given uc
 * @param ucId
 */
void ScheduleManager::printUcStudents(const string &ucId, const string &sortType) const {
    system("clear");
    vector<Student> studentsVector = studentsOfSubject(ucId);
    if(studentsVector.empty()){
        cout << ">> Subject not found" << endl;
        return;
    }
    if (sortType == "alphabetical") {
        sort(studentsVector.begin(), studentsVector.end(), [](const Student &a, const Student &b) { return a.getName() < b.getName(); });
    } else if (sortType == "reverse alphabetical") {
        sort(studentsVector.rbegin(), studentsVector.rend(), [](const Student &a, const Student &b) { return a.getName() < b.getName(); });
    } else if (sortType == "numerical") {
        sort(studentsVector.begin(), studentsVector.end());
    } else if (sortType == "reverse numerical") {
        sort(studentsVector.rbegin(), studentsVector.rend());
    } else {
        cout << "Invalid sortType" << endl;
        return;
    }
    sort(studentsVector.begin(), studentsVector.end(), [](const Student &s1, const Student &s2) {
        return s1.getName() < s2.getName();
    });
    cout << endl << ">> Number of students: " << studentsVector.size() << endl;
    cout << ">> Students:" << endl;
    for (const Student &student: studentsVector) {
        cout << "   "; student.printHeader();
    }
}

/**
* @brief Function that prints all changingRequests in the queue
*/
void ScheduleManager::printPendingRequests() const {
    system("clear");
    queue<Request> pendingRemovalRequests = removalRequests;
    cout << endl << ">> Pending removal requests:" << endl;
    while (!pendingRemovalRequests.empty()) {
        cout << "   "; pendingRemovalRequests.front().printHeader();
        pendingRemovalRequests.pop();
    }
    queue<Request> pendingChangingRequests = changingRequests;
    cout << endl << ">> Pending changing requests:" << endl;
    while (!pendingChangingRequests.empty()) {
        cout << "   "; pendingChangingRequests.front().printHeader();
        pendingChangingRequests.pop();
    }
    queue<Request> pendingEnrollmentRequests = enrollmentRequests;
    cout << endl << ">> Pending enrollment requests:" << endl;
    while (!pendingEnrollmentRequests.empty()) {
        cout << "   "; pendingEnrollmentRequests.front().printHeader();
        pendingEnrollmentRequests.pop();
    }
}

/**
 * @brief Function that prints all the rejected changingRequests
 */
void ScheduleManager::printRejectedRequests() const {
    system("clear");
    cout << endl << ">> Rejected requests:" << endl;
    for (const pair<Request, string> &p: rejectedRequests) {
        cout << "   >> "; p.first.print(); cout <<  "      Reason: " << p.second << endl;
    }
}