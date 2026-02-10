//A simple record with public name and age
#include <iostream>
using namespace std;

class Record {
        private:
          string name;
        int age;
  public:
    Record(){}
    Record(string n, int a){
      name=n;
      age=a;
    }
    //accessor for name
    string get_name(){
      return name;
    }
//accessor for age
    int get_age(){
      return age;
    }
//mutator for name
    void set_name(string name){
      this->name = name;
    }
//mutator for age
    void set_age(int age){
      this->age = age;
    }
  

};