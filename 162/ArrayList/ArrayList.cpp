// ArrayList.cpp
#include "ArrayList.h"

ArrayList::ArrayList() : m_size{0}, m_data{new Record[MAX_SIZE]} {}
int ArrayList::size() const { return m_size; }
// Insert at the end (m_size)
void ArrayList::insert(Record *const val) {
  m_data[m_size] = *val; // need to dereference because argument is a pointer
  ++m_size;
  // added new element so increment element size
}

// print the list
void ArrayList::print_list() const {
  for (int i = 0; i < m_size; ++i) {
    cout << "Name: " << m_data[i].get_name() << ", age: " << m_data[i].get_age()
         << endl;
  }
}
  //finds a person in the list
  int ArrayList::find(const string name, const int age) const{
    for (int i = 0; i < m_size; ++i) {
      if (m_data[i].get_name() == name && m_data[i].get_age() == age ){
        return i;
      }
    }
  cout<<"Record not found."<<endl;
    return -1;
  }
void ArrayList::remove_record(const string name, const int age){
  int pos = find(name,age); //finds what you want to remove
  for (int i= pos; i < m_size ; ++i){ 
    m_data[i] = m_data[i+1]; //cycles through and moves everything to the left
  }
  --m_size;//shrinks the list to get rid of empty space
}
void ArrayList::insertFirst(Record *const val){
for (int i = m_size; i> 0; --i){
  m_data[i] = m_data[i-1];//moves everything over
}
m_data[0] = *val;//inserts val into the first index
++ m_size;//increases size due to new value at beginning
//cout<<m_size<<endl;
}
void ArrayList::insertAtIndex(Record *const val, const int index){
  if (index < 0 || index > m_size-1){
    cout <<"Invalid index."<< endl;//check if index is valid
  }
else
  {
    for (int i = m_size; i > index; --i){//starts at end and goes to index
      m_data[i] = m_data[i-1];//moves everything after index value to right
    }
  ++ m_size;  
  }
  m_data[index] = *val;//sets value in index to user's inserted value
  }
void ArrayList::print_reverse(){
  for (int i = m_size - 1; i >= 0; --i) {//backwards for loop 
    cout << "Name: " << m_data[i].get_name() //print out value at i index
      << ", age: " << m_data[i].get_age()<< endl;
  }
}