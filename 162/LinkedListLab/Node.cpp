#include "Node.h"

Node::Node() : m_next{nullptr}, m_value{Record()} {}
Node::Node(const Record v) : m_next{nullptr}, m_value{v} {}
Node::Node(const Node &n) : m_next{nullptr}, m_value{n.m_value} {}

void Node::set_value(const Record v) { m_value = v; }
void Node::set_next(Node *n) { m_next = n; }
Record Node::value() const { return m_value; }
Node *Node::next() const { return m_next; }