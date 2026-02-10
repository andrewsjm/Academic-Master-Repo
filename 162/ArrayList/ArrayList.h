// ArrayList.h
// My arraylist to store records
#include "Record.h"
#include <iostream>
using namespace std;

class ArrayList {
  // maximum size of records it can hold
  const int MAX_SIZE = 40;

private:
  // My record
  Record *m_data;
  // Size of elements stored
  int m_size;

public:
  ArrayList();
  // size accessor
  int size() const;
  // inserts a record at the end of the list
  void insert(Record *const val);
  // inserts a record at the beginning of the list
  void insertFirst(Record *const val);
  // insert a record at a given index between 0 and m_size-1
  void insertAtIndex(Record *const val, const int index);

  // finds record based on name and returns index if present,       
  //otherwise returns -1
  int find(const string name, const int age) const;
  // removes the record based on name and age and removes it by moving other records up in the list
  void remove_record(const string name, const int age);
  
  // prints the record information
  void print_list() const;
  //print the record in reverse order
  void print_reverse();
};