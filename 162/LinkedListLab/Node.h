#include "Record.h"

class Node {
private:
  Record m_value;
  Node *m_next;
public:
  Node();
  Node(const Record v);
  Node(const Node &n);
  void set_value(const Record v);
  void set_next(Node *n);
  Record value() const;
  Node *next() const;
};