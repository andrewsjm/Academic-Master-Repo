#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;
int main(int argc, char* argv[]) {
  if (argc != 2) {                                                                              // Check for the correct number of command-line arguments
    cerr << "Usage: " << argv[0] << " <path_to_db>" << endl;
    return 1;
  }

  sqlite3* db = nullptr;                                                                        // Pointer to SQLite database
  int result = sqlite3_open_v2(argv[1], &db, SQLITE_OPEN_READWRITE, nullptr);                   // Open SQLite connection
  if (result != SQLITE_OK) {
    cerr << "Failed to open database. Error: " << sqlite3_errmsg(db) << endl;
    sqlite3_close(db);
    return 1;
  }

  const char* allCoursesQuery = "SELECT * FROM courses";                                        // Query to select all courses from the database
  sqlite3_stmt* stmt = nullptr;                                                                 // Statement object to represent SQL queries

  result = sqlite3_prepare_v2(db, allCoursesQuery, -1, &stmt, nullptr);                         // Prepare an SQL query to select all from the "courses" table
  if (result != SQLITE_OK) {
    cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
    sqlite3_finalize(stmt);                                                                     // Finalize the prepared statement
    sqlite3_close(db);                                                                          // Close the database connection
    return 1;
  }

  cout << "Courses:" << endl;
  while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
    const unsigned char* title = sqlite3_column_text(stmt, 3); 
    cout << title << endl;
  }

  sqlite3_finalize(stmt);
  stmt = nullptr; // Reset stmt for use w new query

  string input;                                                                                 // prompt user for course title to search
  cout << "Enter course title to search: ";
  getline(cin, input);                                                                          // use getline to handle spaces 

  const char* singleCourseQuery = "SELECT * FROM courses WHERE title = ?";                      // Query with placeholder for binding user input

  result = sqlite3_prepare_v2(db, singleCourseQuery, -1, &stmt, nullptr);                       // Prepare query to select courses by title
  if (result != SQLITE_OK) {
    cerr << "Failed to prepare statement. Error: " << sqlite3_errmsg(db) << endl;
    sqlite3_finalize(stmt);                                                                     // Finalize the prepared statement
    sqlite3_close(db);                                                                          // Close the database connection
    return 1;
  }

  result = sqlite3_bind_text(stmt, 1, input.c_str(), -1, SQLITE_TRANSIENT);                     // Bind user input to placeholder
  if (result != SQLITE_OK) {
    cerr << "Failed to bind text. Error: " << sqlite3_errmsg(db) << endl;
    sqlite3_finalize(stmt);                                                                     // Finalize the prepared statement
    sqlite3_close(db);                                                                          // Close the database connection
    return 1;
  }

  cout << "Search Results for: " << input << endl;
  cout << "Title | Course_Num | Section | Period | Enrollment_Cap | Days | Prof_ID" << endl;

  while((result = sqlite3_step(stmt)) == SQLITE_ROW) {                                          // Iterates through each matching result
    const unsigned char* title = sqlite3_column_text(stmt, 3);                                  // Fetch the title from the current row
    const unsigned char* section = sqlite3_column_text(stmt, 2);                                // Fetch the section number from current row
    const unsigned char* course_num = sqlite3_column_text(stmt, 1);                             // Fetch the course number from current row
    const unsigned char* days = sqlite3_column_text(stmt, 4);                                   // Fetch the days from current row
    const unsigned char* period = sqlite3_column_text(stmt, 5);                                 // Fetch the period from current row
    const unsigned char* enrollment_cap = sqlite3_column_text(stmt, 6);                         // Fetch the capacity of the class from current row
    const unsigned char* prof_id = sqlite3_column_text(stmt, 7);                                // Fetch the professor id from current row
    cout << title << " "<<course_num << " "<< section << " "<< period << " "<< enrollment_cap << " "<< days << " "<< prof_id<< endl;
  }

  sqlite3_finalize(stmt);
  //close connection
  sqlite3_close(db);

  return 0;
}