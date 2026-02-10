#include "Record.h"

class Node {
private:
  Record m_value;
  

public:
  Node *left;
  Node *right;
  Node();
  Node(const Record v);
  Node(const Node &n);
  ~Node();
  void set_value(const Record v);
  Record value() const;
};
