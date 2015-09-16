#ifndef NODE_H
#define NODE_H
#include "Link.h"

using namespace std;

class Link;

class Node
{
 //the instructions specified all public member functions and variables,
 //but this is not best practice
 public:
  //the int value of stored inside the node
  int value;
  
  //the pointer to the dynamically allocated array of link pointers
  Link **links;

  //the number of links the node has formed
  int numlinks;

  //constructors
  Node();
  Node(int v);
  
  //public member functions
  Node *findChar(char c);
  
  //destructor
  ~Node();
};

#endif
