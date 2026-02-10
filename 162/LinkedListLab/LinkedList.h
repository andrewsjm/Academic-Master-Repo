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