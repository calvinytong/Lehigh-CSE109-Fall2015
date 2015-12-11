#include <string>
#include <vector>
#include <ostream>
#include "Node.h"

namespace prog8lib
{
  Node::Node(string s):value(s), distance(-1), parent(NULL)
  {

  }

  Node::Node():value(NULL)
  {

  }

  Node::~Node()
  {

  }

  void Node::createVertex(Node *n)
  {
    neighbors.push_back(n);
  }

  ostream& operator<<(ostream &os, Node &n)
  {
    os << n.value;
    return os;
  }
}
