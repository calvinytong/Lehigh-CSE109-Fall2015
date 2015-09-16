#ifndef Link_H
#define Link_H

#include "Node.h"
using namespace std;

class Node;

class Link
{
 //the assignment said to have all public members, note that this is not best practice
 public:
  //the letter held in the link
  char letter;
  
  //pointer to the next node
  Node *next;

  //constructor
  Link(char l, Node *n);
  
  //destructor
  ~Link();
};

#endif
