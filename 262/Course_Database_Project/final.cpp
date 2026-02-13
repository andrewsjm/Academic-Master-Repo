#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <sqlite3.h>

using namespace std;

// Function Declarations
void printAllCourses(sqlite3* db);
void listCoursesByProfessor(sqlite3* db);
void listCoursesBySubject(sqlite3* db);
void addCourseToDatabase(sqlite3* db);
void listCoursesByTimeRange(sqlite3* db);
void registerStudentForClasses(sqlite3* db);
void showStudentSchedule(sqlite3* db);
void dumpProfessorsInfo(sqlite3* db);
void dumpStudentsInfo(sqlite3* db);
void updateCourseTitle(sqlite3* db);
void dumpCoursesInfo(sqlite3* db);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <path_to_db>" << endl;
        return 1;
    }

    sqlite3* db = nullptr;
    int result = sqlite3_open_v2(argv[1], &db, SQLITE_OPEN_READWRITE, nullptr);
    if (result != SQLITE_OK) {
        cerr << "Failed to open database. Error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }
        string input;
    while (true) {
        cout << "Choose an option:" << endl;
        cout << "A: Print all courses" << endl;
        cout << "B: List courses by subject" << endl;
        cout << "C: List courses by professor" << endl;
        cout << "D: Add course to database" << endl;
        cout << "E: List courses by Time" << endl;
        cout << "F: Register Student for Classes" << endl;
        cout << "G: Show Student Schedule" << endl;
        cout << "H: Dump all Professor data" << endl;
        cout << "I: Dump all Student data" << endl;
        cout << "J: Dump all Courses data" << endl;
        cout << "K: Change course title based on ID" << endl;
        cout << "Type 'quit' to exit" << endl;
        cout << "Enter choice: ";
        getline(cin, input);

        if (input == "quit") {
            cout << "Have a nice day!" << endl;
            break;
        }

        switch (input[0]) {
            case 'A':
                printAllCourses(db);
                break;
            case 'B':
                listCoursesBySubject(db);
                break;
            case 'C':
                listCoursesByProfessor(db);
                break;
            case 'D':
                addCourseToDatabase(db);
                break;
            case 'E':
                listCoursesByTimeRange(db);
                break;
            case 'F':
                registerStudentForClasses(db);
                break;
            case 'G':
                showStudentSchedule(db);
                break;
            case 'H':
                dumpProfessorsInfo(db);
                break;
        case 'I':
                dumpStudentsInfo(db);
                break;
        case 'J':
                dumpCoursesInfo(db);
                break;
        case 'K':
            updateCourseTitle(db);
                break;

        default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
   
    sqlite3_close(db);

    return 0;
}

void printAllCourses(sqlite3* db) {
    const char* query = "SELECT course_id, title, number, subject FROM Courses";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "All Courses:" << endl;
    bool hasResults = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        hasResults = true;
        int courseId = sqlite3_column_int(stmt, 0);
        const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* courseNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* subject = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        cout << "Course ID: " << courseId << ", Title: " << title
             << ", Number: " << courseNumber << ", Subject: " << subject << endl;
    }

    if (!hasResults) {
        cout << "No courses found." << endl;
    }

    sqlite3_finalize(stmt);
}


void listCoursesBySubject(sqlite3* db) {
    string subject;
    cout << "Enter subject to list courses (e.g., CMSC): ";
    getline(cin, subject);

    const char* query = "SELECT course_id, title, number FROM Courses WHERE subject = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, subject.c_str(), -1, SQLITE_TRANSIENT);

    cout << "Courses in the subject " << subject << ":" << endl;
    bool hasResults = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        hasResults = true;
        int courseId = sqlite3_column_int(stmt, 0);
        const unsigned char* title = sqlite3_column_text(stmt, 1);
        const unsigned char* courseNumber = sqlite3_column_text(stmt, 2);
        cout << "Course ID: " << courseId << ", Title: " << title << ", Number: " << courseNumber << endl;
    }

    if (!hasResults) {
        cout << "No courses found for the subject: " << subject << endl;
    }

    sqlite3_finalize(stmt);
}


void listCoursesByProfessor(sqlite3* db) {
    int professorId;
    cout << "Enter professor ID to view their course schedule: ";
    cin >> professorId;
    cin.ignore();

    const char* query = "SELECT p.name, c.title, c.number, s.days, s.number, s.startPeriod, s.endPeriod "
                        "FROM Sections AS s "
                        "JOIN Courses AS c ON s.course_id = c.course_id "
                        "JOIN Professors AS p ON s.professor_id = p.professor_id "
                        "WHERE s.professor_id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, professorId);

    // Check if at least one row is returned to confirm the professor's ID is valid
    bool hasResults = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (!hasResults) {
            const unsigned char* professorName = sqlite3_column_text(stmt, 0);
            cout << "Course Schedule for Professor ID " << professorId << " (" << professorName << "):" << endl;
            hasResults = true;
        }
        const unsigned char* title = sqlite3_column_text(stmt, 1);
        const unsigned char* courseNumber = sqlite3_column_text(stmt, 2);
        const unsigned char* sectionDays = sqlite3_column_text(stmt, 3);
        const unsigned char* sectionNumber = sqlite3_column_text(stmt, 4);
        int sectionStartPeriod = sqlite3_column_int(stmt, 5);
        int sectionEndPeriod = sqlite3_column_int(stmt, 6);
        cout << "Title: " << title << ", Course Number: " << courseNumber 
             << ", Days: " << sectionDays << ", Section Number: " << sectionNumber
             << ", Period: " << sectionStartPeriod << "-" << sectionEndPeriod << endl;
    }

    if (!hasResults) {
        cout << "No courses found for Professor ID " << professorId << endl;
    }

    sqlite3_finalize(stmt);
}


void addCourseToDatabase(sqlite3* db) {
    // Data for the Courses table
    string title, courseNumber, subject;
    int courseId;

    // Data for the Sections table
    int sectionNumber, professorId, crn, startPeriod, endPeriod;
    string days;

    // Input for Courses table
    cout << "Enter course title: ";
    getline(cin, title);
    cout << "Enter course number: ";
    getline(cin, courseNumber);
    cout << "Enter course subject: ";
    getline(cin, subject);

    // Insert course into Courses table
    const char* courseQuery = "INSERT INTO Courses (title, number, subject) VALUES (?, ?, ?)";
    sqlite3_stmt* courseStmt;

    if (sqlite3_prepare_v2(db, courseQuery, -1, &courseStmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare course statement. Error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(courseStmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(courseStmt, 2, courseNumber.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(courseStmt, 3, subject.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(courseStmt) != SQLITE_DONE) {
        cerr << "Failed to execute course statement. Error: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Course added successfully." << endl;
    }

    sqlite3_finalize(courseStmt);

    // Get the last inserted course_id
    courseId = sqlite3_last_insert_rowid(db);

    // Input for Sections table
    cout << "Enter section number: ";
    cin >> sectionNumber;
    cout << "Enter CRN: ";
    cin >> crn;
    cout << "Enter the start of the period without a colon: ";
    cin >> startPeriod;
    cin.ignore();
    cout << "Enter the end of the period without a colon: ";
    cin >> endPeriod;
    cin.ignore();
    cout << "Enter days (e.g., MWF or TTh): ";
    getline(cin, days);
    cout << "Press enter again please.";                //For some reason you just have to in order to progress, my guess is something to do with the ignore
    cin.ignore();
    cout << "Enter professor ID: ";
    cin >> professorId;
    cin.ignore();

    // Insert section into Sections table
    const char* sectionQuery = "INSERT INTO Sections (course_id, professor_id, crn, number, days, startPeriod, endPeriod) VALUES (?, ?, ?, ?, ?, ?, ?)";
    sqlite3_stmt* sectionStmt;

    if (sqlite3_prepare_v2(db, sectionQuery, -1, &sectionStmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare section statement. Error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(sectionStmt, 1, courseId);
    sqlite3_bind_int(sectionStmt, 2, professorId);
    sqlite3_bind_int(sectionStmt, 3, crn);
    sqlite3_bind_int(sectionStmt, 4, sectionNumber);
    sqlite3_bind_text(sectionStmt, 5, days.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(sectionStmt, 6, startPeriod);
    sqlite3_bind_int(sectionStmt, 7, endPeriod);

    if (sqlite3_step(sectionStmt) != SQLITE_DONE) {
        cerr << "Failed to execute section statement. Error: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Section added successfully." << endl;
    }

    sqlite3_finalize(sectionStmt);
}

void listCoursesByTimeRange(sqlite3* db) {
    string days;
    int startPeriod, endPeriod;

    cout << "Enter days (e.g., MWF or TTh): ";
    getline(cin, days);
    cout << "Enter start period: ";
    cin >> startPeriod;
    cout << "Enter end period: ";
    cin >> endPeriod;
    cin.ignore();  // Clear the newline character from the input buffer

    const char* query = "SELECT c.title, c.number, s.days, s.number, s.startPeriod, s.endPeriod "
                        "FROM courses AS c "
                        "JOIN sections AS s ON c.course_id = s.course_id "
                        "WHERE s.days = ? AND s.startPeriod <= ? AND s.endPeriod >= ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, days.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, startPeriod);
    sqlite3_bind_int(stmt, 3, endPeriod);

    cout << "Courses on " << days << " between periods " << startPeriod << " and " << endPeriod << ":" << endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* title = sqlite3_column_text(stmt, 0);
        const unsigned char* courseNumber = sqlite3_column_text(stmt, 1);
        const unsigned char* sectionDays = sqlite3_column_text(stmt, 2);
        const unsigned char* sectionNumber = sqlite3_column_text(stmt, 3);
        int sectionStartPeriod = sqlite3_column_int(stmt, 4);
        int sectionEndPeriod = sqlite3_column_int(stmt, 5);
        cout << "Title: " << title << ", Course Number: " << courseNumber 
             << ", Days: " << sectionDays << ", Section Number: " << sectionNumber
             << ", Period: " << sectionStartPeriod << "-" << sectionEndPeriod << endl;
    }

    sqlite3_finalize(stmt);
}


void registerStudentForClasses(sqlite3* db) {
    int studentId, courseId;
    cout << "Enter student ID: ";
    cin >> studentId;
    cin.ignore();

    vector<int> courseIds;
    string input;
    cout << "Enter course IDs to register (separated by space, press ENTER when done): ";
    getline(cin, input);
    stringstream ss(input);
    while (ss >> courseId) {
        courseIds.push_back(courseId);
    }

    const char* query = "INSERT INTO registration (student_id, course_id) VALUES (?, ?)";
    sqlite3_stmt* stmt;

    for (auto id : courseIds) {
        if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
            cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
            continue;
        }

        sqlite3_bind_int(stmt, 1, studentId);
        sqlite3_bind_int(stmt, 2, id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Failed to execute statement. Error: " << sqlite3_errmsg(db) << endl;
        } else {
            cout << "Student ID " << studentId << " registered for course ID " << id << "." << endl;
        }

        sqlite3_finalize(stmt);
    }
}

void showStudentSchedule(sqlite3* db) {
    int studentId;
    cout << "Enter student ID to view the course schedule: ";
    cin >> studentId;
    cin.ignore();

    const char* query = "SELECT c.title, c.course_num, c.section, c.period, c.days "
                        "FROM courses AS c "
                        "JOIN registration AS r ON c.course_id = r.course_id "
                        "WHERE r.student_id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, studentId);

    cout << "Course Schedule for Student ID " << studentId << ":" << endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* title = sqlite3_column_text(stmt, 0);
        const unsigned char* course_num = sqlite3_column_text(stmt, 1);
        const unsigned char* section = sqlite3_column_text(stmt, 2);
        const unsigned char* period = sqlite3_column_text(stmt, 3);
        const unsigned char* days = sqlite3_column_text(stmt, 4);
        cout << title << " (" << course_num << "), Section: " << section << ", Period: " << period << ", Days: " << days << endl;
    }

    sqlite3_finalize(stmt);
}
void updateCourseTitle(sqlite3* db) {
    int courseId;
    string newTitle;
    cout << "Enter Course ID to update: ";
    cin >> courseId;
    cin.ignore();
    cout << "Enter new course title: ";
    getline(cin, newTitle);

    const char* query = "UPDATE Courses SET title = ? WHERE course_id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, newTitle.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, courseId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Failed to execute statement. Error: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Course title updated successfully." << endl;
    }

    sqlite3_finalize(stmt);
}


void dumpProfessorsInfo(sqlite3* db) {
    const char* query = "SELECT professor_id, name FROM Professors";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Professors Information:" << endl;
    bool hasResults = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        hasResults = true;
        int professorId = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        cout << "Professor ID: " << professorId << ", Name: " << name << endl;
    }

    if (!hasResults) {
        cout << "No professors found." << endl;
    }

    sqlite3_finalize(stmt);
}
void dumpStudentsInfo(sqlite3* db) {
    const char* query = "SELECT student_id, name FROM Students";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Students Information:" << endl;
    bool hasResults = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        hasResults = true;
        int studentId = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        cout << "Student ID: " << studentId << ", Name: " << name << endl;
    }

    if (!hasResults) {
        cout << "No students found." << endl;
    }

    sqlite3_finalize(stmt);
}
void dumpCoursesInfo(sqlite3* db) {
    const char* query = "SELECT course_id, title, number, subject FROM Courses";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "Courses Information:" << endl;
    bool hasResults = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        hasResults = true;
        int courseId = sqlite3_column_int(stmt, 0);
        const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* courseNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* subject = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        cout << "Course ID: " << courseId << ", Title: " << title
             << ", Number: " << courseNumber << ", Subject: " << subject << endl;
    }

    if (!hasResults) {
        cout << "No courses found." << endl;
    }

    sqlite3_finalize(stmt);
}
