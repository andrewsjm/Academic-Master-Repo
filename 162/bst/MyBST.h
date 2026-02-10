#include "Node.h"
#include <iostream>

class MyBST {
  Node *m_root;
  int m_size;

public:
  MyBST();
  MyBST(const Record &v);
  ~MyBST();

  Node *insert(Node *root, const Record &v);
  int size();
  Node *get_root();
  void print(const Record &v);

  bool search(Node *root, int age);
  void inorder(Node *root); // Print name, age, Eg: Mandy, 10
  void preorder(Node *root);
  void postorder(Node *root);

};