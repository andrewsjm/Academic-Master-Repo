#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() : m_head{nullptr}, m_size{0} {}
//Delete all the elements of the list
LinkedList::~LinkedList() {
  Node *next = m_head;
  while (m_head != nullptr) {
    next = m_head->next();
    delete m_head;
    m_head = next;
  }
}
//adds element to the front of the list
void LinkedList::insertFront(const Record &v) {
  Node *n = new Node{v};        //adds new element
  n->set_next(m_head);          //sets new element to the head  
  m_head = n;                   //sets the value to the desired one
  ++m_size;                     //adds size because new element is added
}
//adds element to end of the list
void LinkedList::insertEnd(const Record &v){
  //Node *p = nullptr;
  Node *cur= m_head;            //sets cur pointer
  //Node *n = new Node{v};

 while (cur->next() != nullptr){ //loops through each element until null value
    cur = cur->next();          //sets cur to last element
 }      
 Node *n = new Node{v};
 cur-> set_next(n);             //sets desired value to cur   
++m_size;                       //increases size 
} 

void LinkedList::insert(const int index, const Record &v){
  if (index == m_size+1){//checks if index is at last place
    insertEnd(v);//uses insert end to put it at the end
    }
  else if( index == 0){//checks if index is in first place
    insertFront(v);//sets first spot to the given value
  }
  else if (index > m_size+1 || index < 0){//checks to see if index is possible
cout<< "Invalid index."<<endl;
  }
  else{
        Node *cur = m_head;
        Node *prev;
        for (int i = 0 ; i < index; ++i){       //loops through until it gets to desired index
        prev = cur;                             //saves the previous val
        cur = cur->next();                      //moves to index
        }
        //Node *two = cur;//saves value of previous at index
        Node *n = new Node{v};
        //cur = n;
        prev->set_next(n); 
        n->set_next(cur);                       //sets the index to 
        ++m_size;
  }
  }
//--m_size; //there was an invalid amount of elements in the couter, there was an extra element in every question after this one so i threw this in to fix that.

void LinkedList::removeFront(){
  Node *prev = nullptr;         
  Node *cur = m_head;
  Node *x = m_head;                             //sets a pointer to head
m_head = x->next();                             //sets head to pointer
  delete x;                                     //deletes pointer which deletes head
--m_size;                                       //decrease size due to removal
}
void LinkedList::remove(const int index){
  Node *prev = nullptr;
  Node *cur = m_head;
  if (index == 0){                      //checks if index is at front
    removeFront();                      //uses function from earlier
  }
  else if (!(index > m_size || index < 0)){     //checks if index is valid using negation
    for (int i = 0; i < index; ++i){            //cycles through until index
      prev = cur;
      cur = cur->next();                        //sets pointer to index place
    }
prev->set_next(cur->next());                    //moves prev up to make sure no empty space
    delete cur;                                 //deletes indexed value
    --m_size;                                   //decrease size becaue of removal
  }
}
//Prints the element from the front to end       
       void LinkedList::print() const {
  Node *cur = m_head;
  int i = 0;
  while (cur != nullptr) {
    cout << i++ << ": Name: " << cur->value().get_name()
         << ", age: " << cur->value().get_age() << endl;
    cur = cur->next();
  }
  cout << "Total elements: " << m_size << endl;
}
Node *LinkedList::find(int age) const {
   Node *cur = m_head;
   while (cur != nullptr) {
     if (cur->value().get_age() == age)
       return cur;
     cur = cur->next();
   }
   return nullptr;
 }
void LinkedList::updateRecord(const string name, const int age, const Record &v){
  int index = 0;
  Node *cur = m_head;
  Node *n = new Node{v};
  while (cur != nullptr){               //loops through to find record to update
    ++ index;
    if (find(name) && find(age)){       //checks if record is the desired one to update
      remove(index);                    //removes the value at index
      insert(index, v);                 //inserts new value to replace removed
    }
else{
  cout <<"Record not found."<<endl;
  }
  break;
  } 
}
Node *LinkedList::find(string name) const {
  Node *cur = m_head;
  while (cur != nullptr) {
    if (cur->value().get_name() == name)
      return cur;
    cur = cur->next();
  }
  return nullptr;
}

void LinkedList::remove(const string name) {
  Node *prev = nullptr;
  Node *cur = m_head;
  while (cur != nullptr) {
    if (cur->value().get_name() == name) {
      if (prev == nullptr) {//case that there is only one element
        m_head = m_head->next();
      } else {
        prev->set_next(cur->next());
      }
      delete cur;//delete the record to free memory
      return;
    }
    prev = cur; //update the previous to current element
    cur = cur->next(); //update the current element to its next
  }
  --m_size;
}
int LinkedList::get_size() { return m_size; }