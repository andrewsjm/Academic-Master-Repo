#include "Node.h"

Node::Node() : left{nullptr}, right{nullptr}, m_value{Record()} {}
Node::Node(const Record v) : left{nullptr}, right{nullptr}, m_value{v} {}
Node::Node(const Node &n) : left{nullptr}, right{nullptr}, m_value{n.m_value} {}
Node::~Node() {
  delete left;//delete left pointer
  delete right; //delete right pointer
}

void Node::set_value(const Record v) { m_value = v; }
Record Node::value() const { return m_value; }