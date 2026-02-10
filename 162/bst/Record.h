// A simple record with public name and age
#include <iostream>
using namespace std;

class Record {
private:
  string name;
  int age;

public:
  Record() {}
  Record(string n, int a) {
    name = n;
    age = a;
  }
  string get_name() const { return name; }
  int get_age() const { return age; }
  void set_name(string s) { name = s; }
  void set_age(int a) { age = a; }
};