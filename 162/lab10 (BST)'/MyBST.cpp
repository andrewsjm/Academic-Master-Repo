#include "MyBST.h"
//#include "Node.h"
#include <iostream>

using namespace std;
//Constructors
MyBST::MyBST() : m_root{nullptr}, m_size{0} {}
//Constructor to add a record as root of the node (the first element)
MyBST::MyBST(const Record &v) {
  m_root = new Node{v};
  m_size = 0;
  ++m_size;//need to add the size since just added a record as node
}
MyBST::~MyBST() {
  delete m_root; // delete starting from root and it will call delete to other
                 // nodes
}

Node *MyBST::get_root() { return m_root; }
// Priting name and age of record, use this print when printing
void MyBST::print(const Record &v) {
  cout << v.get_name() << ", " << v.get_age() << endl;
}

int MyBST::size() { return m_size; }

Node *MyBST ::insert(Node *root, const Record&v){
  if (!root){
    //insert first node if root is null
    Node *n = new Node{v};
    ++m_size;
    return n;
  }
  if (v.get_age() > root -> value().get_age()){
    //insert right node if value is greater than root
    root ->right = insert(root->right, v);
  }
  else if (v.get_age() < root -> value().get_age()){
    //insert left node if value is lesser than root
    root->left = insert(root->left, v);
  }
  return root;
}
void MyBST::inorder(Node* root){
 if (!root){
   return;
 }
 inorder(root->left);
 //goes up from the left side to the root to put in order
 print(root->value());
 //uses print function to print 
 inorder (root->right);
// goes and gets the elements on the right to put after the left and root
}

bool MyBST::search(Node *root, int age){
  if (root == NULL){
    return false;
}
else if (age < root ->value().get_age()){
  return search(root->left, age);
}
else if (root->value().get_age() == age){
  return true;
}
else{ 
return search(root->right, age);}
}
void MyBST::preorder(Node* root){
  if (!root){
    //if the root is null return 
  return;
  }
  print(root->value());
  //uses the print function first to print the elements in pre-order
  preorder(root->left);
  //puts the stuff on the left in
  preorder(root->right);
  //puts stuff on right in
}
void MyBST::postorder(Node *root){
  if (!root){
    //if no root, return
    return;
  }
  postorder(root->left);
  //gets the stuff on the left
  postorder(root->right);
  //gets elts on right
  print(root->value());
  //prints in post-order format
}