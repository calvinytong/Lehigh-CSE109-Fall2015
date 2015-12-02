#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <ostream>

using namespace std;

namespace prog8lib
{
  class Node
  {
   public:
     string value;
     vector<Node*> neighbors;

     Node();
     Node(string s);
     
     void createVertex(Node *n);

     ~Node();

     friend ostream& operator<<(ostream& os, Node &n);
  };

}
#endif
