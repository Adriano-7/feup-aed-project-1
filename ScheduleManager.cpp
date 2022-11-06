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
*@details Creates a Schedule Manager with an empty set of students, a empty vector of schedules, empty queues of requests and an empty vector of rejectedRequests\n
*Time complexity: O(1)
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
 * @details Time complexity: O(n) + O(m log n) + O(p log n) being n the number of lines in the file classes_per_uc, m the number of lines in the file classes.csv and p the number of lines in the file student_classes.csv
 * @see createSchedules()
 * @see setSchedules()
 * @see createStudents()
*/
void ScheduleManager::readFiles() {
    createSchedules(); // O(n)
    setSchedules(); // O(m log n)
    createStudents(); // O(p log n
}

/**
*@brief Reads the file "classes_per_uc.csv" and creates a vector of schedules with only UcCLass (without students or slots)
*@details Time complexity: O(n), being n the number of lines in the file "classes_per_uc.csv" (which happens to be the number of schedules)
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
        while(getline(str, word, ',')) //Number of words per line is constant(O(1))
            row.push_back(word);
        UcClass ucClass(row[0], row[1]);
        ClassSchedule cs(ucClass);
        schedules.push_back(cs);
    }
}

/**
* @brief Reads the file "classes.csv" and updates the vector schedules with information about the slots
* @details Time complexity: O(m log n), being m the number of lines in the file classes.csv (number of slots) and  n the number of schedules as seen previously
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
        while (getline(str, word, ',')) //Number of words per line is constant(O(1)
            row.push_back(word);
        string classCode = row[0], ucCode = row[1], weekDay = row[2], startTime = row[3], duration = row[4], type = row[5];
        UcClass ucClass(ucCode, classCode);
        Slot slot(weekDay, stof(startTime), stof(duration), type);
        unsigned long scheduleIndex = binarySearchSchedules(ucClass);  //O(log n)
        if (scheduleIndex != -1) {
            schedules[scheduleIndex].addSlot(slot);
        }
    }
}

/**
 * @brief Reads the file "students.csv" and creates/updates the student information and set of students
* @detailes Reads the students_classes.csv file, adds/updates the student information by adding the UcClass read in the file. It also inserts/updates the student in the set of students\n
* Time complexity: O(p log s), being p the number of lines in the file students_classes.csv and s the number of students
*/
void ScheduleManager::createStudents() {
    fstream file("../data/students_classes.csv");
    file.ignore(1000, '\n');
    vector<string> row;
    string line, word;
    while (getline(file, line)) { //O(p), being p the number of lines in the file students_classes.csv
        row.clear();
        if (line[line.size() - 1] == '\r')
            line.resize(line.size() - 1);
        stringstream str(line);
        while (getline(str, word, ',')) //Number of words per line is constant(O(1)
            row.push_back(word);
        string id = row[0], name = row[1];

        UcClass newUcClass = UcClass(row[2], row[3]);
        unsigned long i = binarySearchSchedules(newUcClass); //O(log n) where n is the number of schedules(lines in the classes_per_uc.csv file)
        Student student(id, name);

        if (students.find(student) == students.end()) {
            student.addClass(this->schedules[i].getUcClass());
            students.insert(student); //O(log n)
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
* @details Uses binary search to find the schedules \n
* Time complexity: O(log n) where n is the number of schedules(lines in the classes_per_uc.csv file)
* @return The index of the schedule with the ucClass passed as parameter
* @see Slot::overlaps()
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
* @brief Function that returns the student with the ID passed as parameter
 * @details Time complexity: O(log p) where p is the number of students in the set of students
* @param studentId
*/
Student* ScheduleManager::findStudent(const string &studentId) const{
    auto student = students.find(Student(studentId, "")); //O(log p)
    return student == students.end() ? nullptr : const_cast<Student*>(&(*student));
}

/**
* @brief Function that returns the schedule with the ucClass passed as parameter
 * @details Time complexity: O(log n) where n is the number of schedules(lines file classes_per_uc.csv) @see binarySearchSchedules()
* @param ucClass
*/
ClassSchedule* ScheduleManager::findSchedule(const UcClass &ucClass) const {
    unsigned long index = binarySearchSchedules(ucClass); //O(log n)
    if(index == -1) return nullptr;
    return const_cast<ClassSchedule*>(&schedules[index]);
}

/**
 * @brief Function that returns a vector with the ClassSchedules of a given class
 * @details Time complexity: O(n) where n is the number of schedules(lines in the classes_per_uc.csv file)
 * @param ucCode
 * @return A vector with all the classes of a given uc
 */
vector<ClassSchedule> ScheduleManager::classesOfUc(const string &ucId) const {
    vector<ClassSchedule> classes;
    for(const ClassSchedule &cs : schedules){
        if(cs.getUcClass().getUcId() == ucId){
            classes.push_back(cs);
        }
    }
    return classes;
}

/**
 * @brief Function that returns a vector with the students of a given class
 * @param ucCode
 * @details O(n) + O(jq) where n is the number of schedules(lines in classes_per_uc.csv file), j the number of ClassSchedules with a given ucId and q the number of students in a given ClassSchedule cs
 * @return A vector with all the students of a given uc
 */
vector<Student> ScheduleManager::studentsOfUc(const string &ucId) const {
    vector<Student> ucStudents;
    vector<ClassSchedule> ucClasses = classesOfUc(ucId); //O(n)
    for(const ClassSchedule &cs : ucClasses){ //O(jq)
        for(const Student &student : cs.getStudents()){
            ucStudents.push_back(student);
        }
    }
    return ucStudents;
}

/**
 * @brief Function that returns the number of students in a given uc
 * @details returns the size of the vector studentsOfUc \n
 * Time complexity: O(n) + O(jq), where n is the number of schedules(lines in classes_per_uc.csv file), j the number of ClassSchedules with a given ucId and q the number of students in a given ClassSchedule
 */
int ScheduleManager::getNumberOfStudentsUc(const std::string &ucId) const {
    return studentsOfUc(ucId).size();
}

/**
 * @brief Function that gets the number of students in a given class of a given uc
 * @details Time complexity: O(log n) being n the number of schedules, @see findSchedule()
 */
int ScheduleManager::getNumberOfStudentsUcClass(const UcClass &ucClass) const{
    return findSchedule(ucClass)->getStudents().size();
}

/**
 * @brief Function that returns the UcClass that the student is currently enrolled in
 * @details Time complexity: O(h) where h is the number of classes the student is enrolled in @see Student::findUcClass()
 */
UcClass ScheduleManager::getFormerClass(const Request &request) const {
    return request.getStudent().findUcClass(request.getDesiredUcClass().getUcId());
}

/**
 * @brief Function that given a student and the ucClass he wants to change to, adds the request to the queue of changingRequests
 * @details Time complexity: O(1)
 */
void ScheduleManager::addChangingRequest(const Student &student, const UcClass &ucClass) {
    changingRequests.push(Request(student, ucClass, "Changing"));
}

/**
 * @brief Function that given a student and the ucClass he wants to enroll in, adds the request to the queue of enrollmentRequests
 * @details Time complexity: O(1)
 */
void ScheduleManager::addEnrollmentRequest(const Student &student, const UcClass &ucClass) {
    enrollmentRequests.push(Request(student, ucClass, "Enrollment"));
}

/**
 * @brief Function that given a student and the ucClass he wants to withdraw from, adds the request to the queue of removalRequests
 * @details Time complexity: O(1)
 */
void ScheduleManager::addRemovalRequest(const Student &student, const UcClass &ucClass) {
    removalRequests.push(Request(student, ucClass, "Removal"));
}

/**
* @brief Function that verifies if the schedule of two given classes have a conflict
* @details Two UcClasses have a conflict if any pair of slots of the two classes overlap \n
 * Time complexity: O(log n) + O(lr) where n is the number of lines in classes_per_uc.csv, l is the number of slots of the first class and r is the number of slots of the second class
* @return true if the classes have a conflict, false otherwise
*/
bool ScheduleManager::classesOverlap(const UcClass &c1, const UcClass &c2) const{
    if(c1.sameUcId(c2)) return false; //O(1)
    ClassSchedule* cs1 = findSchedule(c1); //O(log n) being n the number of schedules
    ClassSchedule* cs2 = findSchedule(c2); //O(log n)
    for(const Slot &slot1 : cs1->getSlots()){   //O(lr) being l the number of slots of cs1 and r the number of slots of cs2
        for(const Slot &slot2 : cs2->getSlots()){
            if(slot1.overlaps(slot2)) return true;
        }
    }
    return false;
}

/**
* @brief Function that verifies if a given request has a conflict with the schedule of a given student
* @details A request has a conflict with the schedule if the class that student wants to enroll in causes a conflict with any of the current classes of the student\n
 * Time complexity: O(t*log n + t*lr) where t is the number of classes the student is enrolled in, and n, l, r are the variables seen in @see classesOverlap()
* @param request
* @return true if the request has a conflict with the schedule of the student, false otherwise
*/
bool ScheduleManager::requestHasCollision(const Request &request) const{
    Student student = request.getStudent(); //O(1)
    UcClass desiredClass = request.getDesiredUcClass(); //O(1)
    vector<UcClass> studentClasses = student.getClasses(); //O(1)
    for (const UcClass &ucClass : studentClasses){
        if(classesOverlap(ucClass, desiredClass)) return true; //(log n) + O(lr)
    }
    return false;
}

/**
 * @brief Function that verifies if by changing to the new class, the student will exceed the max number of students allowed.
 * @details The cap (maximum number of students in a class) is set to be the maximum number of students currently enrolled in q class.
 * If all classes have  the same number of students (and therefor the cap wouldn't  allow a new student to enroll), the cap is set to the maximum number of students in a class + 1.\n
 * Time complexity: O(nlog n) where n is the number of schedules (lines in the classes_per_uc.csv file)
 */
bool ScheduleManager::requestExceedsCap(const Request &request) const{
    vector < ClassSchedule> classesUc = classesOfUc(request.getDesiredUcClass().getUcId());  //O(n) where n is the number of schedules
    sort(classesUc.begin(), classesUc.end(), [](const ClassSchedule &c1, const ClassSchedule &c2){  //O(nlog n)
                                            return c1.getStudents().size() < c2.getStudents().size();
    });

    int cap = classesUc.back().getNumStudents();
    if(classesUc[0].getNumStudents() == cap) cap++;
    return cap < getNumberOfStudentsUcClass(request.getDesiredUcClass()) + 1;
}


/**
 * @brief Function that verifies if the change to the new class provokes disequilibrium.
 * @details In our program we say disequilibrium occurs if by changing to the new class the
 * difference between the number of students of the classes he comes from and goes to is greater
 * than 4. If he comes from a class with more students to a class with less students it doesn't provoke disequilibrium.\
 * If he comes from a class with less students to a class with more students it does provoke disequilibrium if the difference of the number of students is 4 or greater.\n
 *
 * Time complexity: O(log n) where n is the number of schedules (lines in the classes_per_uc.csv file)
 */
bool ScheduleManager::requestProvokesDisequilibrium(const Request &request) const {
    int numFormerClass = getNumberOfStudentsUcClass((getFormerClass(request))) -1; //O(log n)
    int numNewClass = getNumberOfStudentsUcClass(request.getDesiredUcClass()) + 1;

    return (numNewClass) - (numFormerClass) >= 4;
}

/**
 * @brief Function that processes the changingRequests in the queue
 * @details if the request has any problem (conflict, disequilibrium, cap exceeded) it is added to the queue of failedRequests, otherwise it is processed and the student is removed from the former class and added to the new class\n
 * Time complexity: O(t*log n + t*lr) + O(nlog n) where n is the number of schedules (lines in the classes_per_uc.csv file) t, l, r are the variables seen in @see requestHasCollision()
 */
void ScheduleManager::processChangingRequest(const Request &request) {
    if(requestHasCollision(request)){ //O(t*log n + t*lr)
        rejectedRequests.emplace_back(request, "Collision in the students' schedule");
    }
    else if(requestExceedsCap(request)){ //O(nlog n) where n is the number of schedules (lines in the classes_per_uc.csv file)
        rejectedRequests.emplace_back(request, "Exceeds maximum number of students allowed in the class");
    }
    else if(requestProvokesDisequilibrium(request)){ //O(log n)
        rejectedRequests.emplace_back(request, "Change provokes disequilibrium between classes");
    }
    else{
        Student* student = findStudent(request.getStudent().getId()); //O(log n)
        UcClass ucClass = findSchedule(request.getDesiredUcClass())->getUcClass(); //O(log n)
        UcClass oldClass = student->changeClass(ucClass);
        findSchedule(request.getDesiredUcClass())->addStudent(*student);
        findSchedule(oldClass)->removeStudent(*student);
        cout << "   "; request.printHeader();
    }
}

/**
 * @brief Function that processes the removalRequests in the queue
 * @details A Removal request is always accepted\n
 * Time complexity: O(h) + O(log n * log n) + O(log p) where n is the number of schedules (lines in the classes_per_uc.csv file), p is the number of lines in the students.csv file and h is the number of classes of the student submitting the request
 */
void ScheduleManager::processRemovalRequest(const Request &request) {
    Student* student = findStudent(request.getStudent().getId()); // O(log p)
    UcClass ucClass = findSchedule(request.getDesiredUcClass())->getUcClass(); //O(log n)
    student->removeUc(ucClass.getUcId()); //O(h)
    findSchedule(ucClass)->removeStudent(*student); //O(log n * log n)
    cout << "   "; request.printHeader(); cout << endl;
}

/**
 * @brief Function that processes the enrollmentRequests in the queue
 * @details Time complexity: O(t*log n + t*lr) + O(nlog n) + O(log p) where n is the number of schedules (lines in the classes_per_uc.csv file), p is the number of lines in the students.csv file and t, l, r are the variables seen in @see requestHasCollision()
 */
void ScheduleManager::processEnrollmentRequest(const Request &request) {
    if(requestHasCollision(request)){ //O(t*log n + t*lr)
        rejectedRequests.emplace_back(request, "Collision in the students' schedule");
    }
    else if(requestExceedsCap(request)){ //O(nlog n)
        rejectedRequests.emplace_back(request, "Exceeds maximum number of students allowed in the class. Choose another class");
    }
    else{
        Student* student = findStudent(request.getStudent().getId()); //O(log p)
        UcClass ucClass = findSchedule(request.getDesiredUcClass())->getUcClass(); //O(log n)
        student->addUc(ucClass);
        findSchedule(ucClass)->addStudent(*student); //O(log n * log q)
        cout << "   "; request.printHeader();
    }
    cout << endl;
}

/**
 * @brief Function that processes all changingRequests in the queue
 * @details Time complexity: O(h) + O(log n * log n) + O(log p) + O(t*log n + t*lr) + O(nlog n) where n is the number of schedules (lines in the classes_per_uc.csv file), p is the number of lines in the students.csv file, h is the number of classes of the student submitting the request and t, l, r are the variables seen in @see requestHasCollision()
 */
void ScheduleManager::processRequests() {
    cout << ">> Accepted removal requests:" << endl;
    while(!removalRequests.empty()){
        Request request = removalRequests.front();
        removalRequests.pop();
        processRemovalRequest(request); // O(h) + O(log n * log n) + O(log p)
    }
    cout <<endl<< ">> Accepted changing requests:" << endl;
    while(!changingRequests.empty()){
        Request request = changingRequests.front();
        changingRequests.pop();
        processChangingRequest(request); //O(t*log n + t*lr) + O(nlog n)
    }
    cout <<endl<< ">> Accepted enrollment requests:" << endl;
    while(!enrollmentRequests.empty()){
        Request request = enrollmentRequests.front();
        enrollmentRequests.pop();
        processEnrollmentRequest(request); //O(t*log n + t*lr) + O(nlog n) + O(log p)
    }
    if(!rejectedRequests.empty()){
        printRejectedRequests();
    }else{
        cout <<endl<< ">> All Requests were accepted!" << endl;
    }
    string q;
    cout << endl << "Insert any key to continue: ";
    cin >> q;
    cout << endl;
}

/**
 * @brief Function that writes all information to the files
 * @details Time complexity: O(st) where s is the number of students in the set and t is the number of classes of each student
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
* @brief Function that prints all changingRequests in the queue
 * @details Time complexity: O(v)+O(w)+O(z) where v is the number of removal request, w is the number of changing requests and z is the number of enrollment requests
*/
void ScheduleManager::printPendingRequests() const {
    system("clear");
    queue<Request> pendingRemovalRequests = removalRequests;
    cout << endl << ">> Pending removal requests:" << endl;
    while (!pendingRemovalRequests.empty()) { //O(v)
        cout << "   "; pendingRemovalRequests.front().printHeader();
        pendingRemovalRequests.pop();
    }
    queue<Request> pendingChangingRequests = changingRequests;
    cout << endl << ">> Pending changing requests:" << endl;
    while (!pendingChangingRequests.empty()) { //O(w)
        cout << "   "; pendingChangingRequests.front().printHeader();
        pendingChangingRequests.pop();
    }
    queue<Request> pendingEnrollmentRequests = enrollmentRequests;
    cout << endl << ">> Pending enrollment requests:" << endl;
    while (!pendingEnrollmentRequests.empty()) { //O(z)
        cout << "   "; pendingEnrollmentRequests.front().printHeader();
        pendingEnrollmentRequests.pop();
    }
}

/**
 * @brief Function that prints all the rejected changingRequests
 * @details Time complexity: O(a) where a is the number of rejected requests
 */
void ScheduleManager::printRejectedRequests() const {
    system("clear");
    cout << endl << ">> Rejected requests:" << endl;
    for (const pair<Request, string> &p: rejectedRequests) {
        cout << "   >> "; p.first.print(); cout <<  "      Reason: " << p.second << endl;
    }
}

/**
 * @brief  Function converts decimal time to string
 * @details Time complexity: O(1)
 * @param weekdays
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

string ucIdToString(string ucId) {
    /** Maps ucId to uc abbreviation */
    map<string, string> name = {{"L.EIC001", "ALGA"}, {"L.EIC002", "AM I"}, {"L.EIC003", "FP"}, {"L.EIC004", "FSC"}, {"L.EIC005", "MD"}, {"L.EIC011", "AED"}, {"L.EIC012", "BD"}, {"L.EIC013", "F II"}, {"L.EIC014", "LDTS"}, {"L.EIC015", "SO"}, {"L.EIC021", "FSI"}, {"L.EIC022", "IPC"}, {"L.EIC023", "LBAW"}, {"L.EIC024", "PFL"}, {"L.EIC025", "RC"}};
    return name[ucId];
}

struct compareDayWeek
{
    bool operator()(const string d1, const string d2) const
    {
        map <string, int> days = {{"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}, {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}, {"Sunday", 7}};
        return days[d1] < days[d2];
    }
};

/**
 * @brief Function that prints the schedule of a given student
 * @details Time complexity: O()
 * @param studentId
 */

void ScheduleManager::printStudentSchedule(const std::string &studentId) const {
    system("clear");
    Student* student = findStudent(studentId);
    if(student == nullptr) {
        cout << "Student not found!" << endl;
        return;
    }

    //Maps a weekday to a pair of slot/ucId (weekdays and slots are ordered because of map)
    map<string, map<Slot, vector<string>>, compareDayWeek> weekdaySlot;
    vector<UcClass> studentClasses = student->getClasses();

    for (const UcClass &ucClass: studentClasses) {
        ClassSchedule *cs = findSchedule(ucClass);
        for(const Slot &slot: cs->getSlots()){
            weekdaySlot[slot.getWeekDay()][slot].push_back(ucClass.getUcId());
        }
    }
    cout << endl <<  ">> The student " << student->getName() << " with UP number " << student->getId()
    << " is enrolled in the following classes:" << endl << "   ";
    student->printClasses();

    cout << endl << ">> The student's schedule is:" << endl;

    for(const auto &weekday: weekdaySlot) {
        cout << "   >> " << weekday.first << ": " << endl;
        for (const auto &slot: weekday.second) {
            cout << "      " << decimalToHours(slot.first.getStartTime()) << " to "
                 << decimalToHours(slot.first.getEndTime()) << "\t" << slot.first.getType() << "\t";
            for (const string &classId: slot.second) {
                cout << ucIdToString(classId) << " - "<< classId << " ";
            }
            cout << endl;
        }
    }
}

/**
 * @brief Function that prints the schedule of a given class
 * @details Time complexity: O()
 * @param classCode
 */

void ScheduleManager::printClassSchedule(const std::string &classCode) const {
    system("clear");

    //maps a weekday to a pair Slot/ucId. Because we use a map it automatically sorts the weekdays and slots

    map<string, map<Slot, vector<string>>, compareDayWeek> weekdaySlot;

    for(const ClassSchedule &cs: schedules){
        if(cs.getUcClass().getClassId() == classCode){
            for(const Slot &slot: cs.getSlots()){
                weekdaySlot[slot.getWeekDay()][slot].push_back(cs.getUcClass().getUcId());
            }
        }
    }

    if(weekdaySlot.empty()) {cout<<">> Class not found"<<endl; return;}

    cout << ">> The schedule for the class " << classCode << " is:" << endl;
    for(const auto &weekday: weekdaySlot) {
        cout << "   >> " << weekday.first << ": " << endl;
        for (const auto &slot: weekday.second) {
            cout << "      " << decimalToHours(slot.first.getStartTime()) << " to "
                 << decimalToHours(slot.first.getEndTime()) << "\t" << slot.first.getType() << "\t";
            for (const string &classId: slot.second) {
                cout << ucIdToString(classId) << " - "<< classId << " ";
            }
            cout << endl;
        }
    }

}

/**
 * @brief Function that print the schedule of a given uc
 * @details Time complexity: O(n³)
 * @param ucCode
 */
void ScheduleManager::printUcSchedule(const string &ucCode) const{
    system("clear");
    map<string, map<Slot, vector<string>>, compareDayWeek> days; // connects the day of the week with slots (each slot may have different classCode)

    for(const ClassSchedule &cs : schedules){
        if(cs.getUcClass().getUcId() == ucCode){
            for(const Slot &slot : cs.getSlots()){
                days[slot.getWeekDay()][slot].push_back(cs.getUcClass().getClassId());
            }
        }
    }

    if(days.empty()){
        cout << ">> Uc not found" << endl;
        return;
    }
    cout << ">> The schedule for the Uc " << ucCode << " is:" << endl;
    for(const auto &day: days) {
        cout << "   >> " << day.first << ": " << endl;
        for (const auto &slot: day.second) {
            cout << "      " << decimalToHours(slot.first.getStartTime()) << " to "
                 << decimalToHours(slot.first.getEndTime()) << "\t" << slot.first.getType() << "\t";
            for (const string &classcode: slot.second) {
                cout << classcode << " ";
            }
            cout << endl;
        }
    }
}

/**
 * @brief Function that prints the students of a given class
 * @details Time complexity: O(n log n)
 */
void ScheduleManager::printClassStudents(const UcClass &ucClass, const string &orderType) const{
    ClassSchedule* cs = findSchedule(ucClass); //O(n log n)
    if(cs == nullptr){
        cout << ">> Class not found" << endl;
        return;
    }
    system("clear");
    cout<<">> The students of the class "<<ucClass.getClassId()<<" in the uc " << ucClass.getUcId()<<" are:"<<endl;
    cs->printStudents(orderType);   //O(n log n)
}

/**
 * @brief Function that prints the students enrolled a given uc
 * @details Time complexity O(n²)
 * @param ucId
 */
void ScheduleManager::printUcStudents(const string &ucId, const string &sortType) const {
    system("clear");
    vector<Student> studentsVector = studentsOfUc(ucId);   //O(n²)
    if(studentsVector.empty()){
        cout << ">> Uc not found" << endl;
        return;
    }
    if (sortType == "alphabetical") {
        sort(studentsVector.begin(), studentsVector.end(), [](const Student &a, const Student &b) { return a.getName() < b.getName(); });   //O(n logN)
    } else if (sortType == "reverse alphabetical") {
        sort(studentsVector.rbegin(), studentsVector.rend(), [](const Student &a, const Student &b) { return a.getName() < b.getName(); }); //O(n logN)
    } else if (sortType == "numerical") {
        sort(studentsVector.begin(), studentsVector.end()); //O(n logN)
    } else if (sortType == "reverse numerical") {
        sort(studentsVector.rbegin(), studentsVector.rend()); //O(n logN)
    } else {
        cout << "Invalid sortType" << endl;
        return;
    }
    sort(studentsVector.begin(), studentsVector.end(), [](const Student &s1, const Student &s2) { //O(n logN)
        return s1.getName() < s2.getName();
    });
    cout << endl << ">> Number of students: " << studentsVector.size() << endl;
    cout << ">> Students:" << endl;
    for (const Student &student: studentsVector) { //O(n)
        cout << "   "; student.printHeader();   //O(1)
    }
}