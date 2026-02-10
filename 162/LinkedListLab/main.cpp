#include "Node.h"
#include <iostream>
using namespace std;

class LinkedList {
private:
  int m_size;
  Node *m_head;

public:
  LinkedList();
  ~LinkedList();

  void insertFront(const Record &v);
  Node *find(string name) const;
  void print() const;
  void remove(const string name);
Node *find(int age) const;
  int get_size();
  void insertEnd(const Record &v);
  void insert(const int index, const Record &v);
  void remove(const int index);
  void removeFront();
  void updateRecord(const string name, const int age, const Record &v);
};
[andrewsjm@amdahl lab9]$ cat main.cpp
#include "LinkedList.h"
#include <iostream>
using namespace std;

int main() {
  LinkedList l;
  l.insertFront(Record("James", 20));
  l.insertFront(Record("Benee", 30));
  cout << "Current list contents:\n";
  l.print();
  
  cout << "Q1. After adding elements at the end:\n";
  // Add two elements at the end, first, name= Noah and age =24, Second, name =
  // Minnie, age = 34
  l.insertEnd(Record("Noah", 24));
  l.insertEnd(Record("Minnie", 34));
  l.print();

  cout << "Q2a. Testing adding element at given index:\n";
  // Add two elements at the end, first, name= Noah and age =24, Second, name =
  // Minnie, age = 34
  l.insert(-1, Record("Rick", 33));
  cout << "Q2b. Testing adding element at given index:\n";

  l.insert(0, Record("Rick", 33));
  l.insert(2, Record("Peter", 18));
  // l.insertEnd(Record("Minnie", 34));
  l.print(); 
  cout << "Q3. Testing remove element at front:\n";
  l.removeFront();
  l.print();
 
  cout << "Q4a. Testing remove element at a given index:\n";
  l.remove(3);
  l.print();
  cout << "Q4b. Testing remove element at a given index:\n";
  l.remove(l.get_size() - 1); // remove the last element
  l.print();

  cout << "Q5a. Testing update element matching name and age:\n";
  l.updateRecord("Pete", 18, Record("Pete", 19));
  cout << "Q5b. Testing update element matching name and age:\n";
  l.updateRecord("Peter", 18, Record("Pete", 19));
  l.print();

}