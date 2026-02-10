//main.cpp
#include <iostream>
#include "ArrayList.h"
using namespace std;
int main() {
  //Initialize list elements
  Record r1("John",25);
  Record r2("Mary",28);
  Record r3("John",30);
  //Create list and add records
  ArrayList mylist;
  mylist.insert(&r1);
  mylist.insert(&r2);
  mylist.insert(&r3);
  mylist.insert(new Record("James",23));
  //print originial list
  cout<<"Original list:"<<endl;
  mylist.print_list();
 // Q1 
  cout<<"Q1. Testing find: "<<endl;
  cout<<mylist.find("Mary",28)<<endl;//should print 1
  cout<<mylist.find("Noah", 22)<<endl;//should print -1 and error message
 //End Q1
  
// Q2
  cout<<"Q2. Testing removal record:"<<endl;
  mylist.insert(new Record("Holly",33));
  mylist.remove_record("John",30);
  mylist.print_list();
  //End Q2
//Q3
  cout<<"Testing insert at the first:"<<endl;
  mylist.insertFirst(new Record("Rick",19));
  mylist.insertFirst(new Record("Mary",30));
  mylist.print_list();
//End Q3*/

  //Q4
  cout<<"Testing insert at a given index between 0 and : "<<mylist.size()<< endl;
  mylist.insertAtIndex(new Record("Philip",33),-1);
  mylist.insertAtIndex(new Record("Philip",33),100);
  mylist.insertAtIndex(new Record("Philip",33),2);
  mylist.print_list();      
  //End Q4

  //Q5
  cout<<"Testing printing reverse: "<<endl;
    mylist.print_reverse();
  //End Q5  

  
  
}