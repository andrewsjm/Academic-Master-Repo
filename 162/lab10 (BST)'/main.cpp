#include <iostream>
#include "MyBST.h"
using namespace std;
int main() {


  MyBST b{Record("John",22)};//create a BST with a root node

  // Q1. Insert new records to the list
  b.insert(b.get_root(),  Record("Mandy",10));
  b.insert(b.get_root(),  Record("Cander",30));
  b.insert(b.get_root(),  Record("Rose",20));  
  b.insert(b.get_root(),  Record("Keller",50));
  b.insert(b.get_root(),  Record("Nick",5));
  b.insert(b.get_root(),  Record("Jimmy",25));
  cout<<"List size: "<<b.size()<<endl;
  //Q2. Printing in-order
  cout<<"Printing in-order:\n";
  b.inorder(b.get_root());
// Q3. Testing for searching
  cout<<"Searching for age 30 (found: 1, not found: 0):"<<b.search(b.get_root(), 30)<<endl;
  cout<<"Searching for age 55(found: 1, not found: 0): "<<b.search(b.get_root(), 55)<<endl;

  

  //Q4. Printing pre-order
  cout<<"Printing pre-order:\n";
  b.preorder(b.get_root());

  //Q5. Printing in post-order
  cout<<"Printing post-order:\n";
  b.postorder(b.get_root());


  }